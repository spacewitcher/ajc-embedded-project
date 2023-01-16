#ifndef	__CONTROLLERLOGIC_HPP__
#define	__CONTROLLERLOGIC_HPP__

#include "pipca9685.h"

class ControllerLogic {

    public:
        ControllerLogic();
        ~ControllerLogic();
        void setYellowServoPosition(int angle);
        void setBlueServoPosition(int angle);
        void objectDetected();
        void objectNotDetected();
        void dataDetected();
        void dataTransferred();
    
    private:
        PiPCA9685 *servoController;
        int yellowServoPosition = 0;
        int blueServoPosition = 180;
        bool isObjectDetected = false;
};

#endif