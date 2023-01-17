#include "controllerlogic.hpp"
#include <iostream>
#include <chrono>

#define SWEEP_TIME 3 // Duration of the alternation between 45 and 135 degrees for the blue flag

ControllerLogic::ControllerLogic()
{
    servoController = new PiPCA9685(1, 0x70);
    servoController->initialize();
    setYellowServoPosition(yellowServoPosition);
    setBlueServoPosition(blueServoPosition);
}

ControllerLogic::~ControllerLogic() {
    setYellowServoPosition(0);
    setBlueServoPosition(180);
}

void ControllerLogic::setYellowServoPosition(int angle)
{
    yellowServoPosition = angle;
    servoController->move(1, angle);
}

void ControllerLogic::setBlueServoPosition(int angle)
{
    blueServoPosition = angle;
    servoController->move(2, angle);
}

void ControllerLogic::objectDetected()
{
    isObjectDetected = true;
    std::cout<<"MOVING YELLOW FLAG - An object has been detected"<<std::endl; 
    setYellowServoPosition(90);
    sleep(2);

    //Go to the rest position
    setYellowServoPosition(180);
}

void ControllerLogic::dataDetected()
{
    std::cout<<"MOVING BLUE FLAG - Data has been detected"<<std::endl; 
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + std::chrono::seconds(SWEEP_TIME);

    while (std::chrono::high_resolution_clock::now() < end) {
        setBlueServoPosition(45);
        sleep(1);
        setBlueServoPosition(135);
        sleep(1);
    }

    setBlueServoPosition(180);
}

void ControllerLogic::dataTransferred()
{
    std::cout<<"MOVING BLUE FLAG - Transferring data to the TCP server"<<std::endl; 
    setBlueServoPosition(90);
    
    sleep(1);
    //Go back to initial position
    setBlueServoPosition(180);
}



