#include "raspberrymaster.hpp"
#include "wiringSerial.h"
#include <iostream>
#include <unistd.h>
#include <termios.h>

struct beaconData {
  float temperature;
  float pressure;
  float humidity;
  float Rx;
  float Ry;
  float Rz;
  time_t timestamp;
};

RaspberryMaster::RaspberryMaster()
{
    servomotors = new ControllerLogic();
    receiveDataFromSlave();
}

RaspberryMaster::~RaspberryMaster()
{

}

void RaspberryMaster::receiveDataFromSlave()
{
    int fd = serialOpen("/dev/ttyS0", 115200); // Open the serial port at 9600 baud

    tcflush(fd,TCIFLUSH); // clear buffer in case there's already data before 1st read

    beaconData data;

    while(1)

    {

        char* data_ptr = (char*)&data;
        for(int i=0; i< (int)sizeof(beaconData); i++) {
        *(data_ptr++) = serialGetchar(fd);
        }

        servomotors->dataDetected();

        std::cout << "Timestamp: " << data.timestamp << std::endl;
        std::cout << "Temperature: " << data.temperature << std::endl;
        std::cout << "Pressure: " << data.pressure << std::endl;
        std::cout << "Humidity: " << data.humidity << std::endl;
        std::cout << "Rx: " << data.Rx << std::endl;
        std::cout << "Ry: " << data.Ry << std::endl;
        std::cout << "Rz: " << data.Rz << std::endl;


        serialPuts(fd, "A"); // Send confirmation back to the slave


    }

    serialClose(fd);
}


