#ifndef	__RASPBERRYMASTER_HPP__
#define	__RASPBERRYMASTER_HPP__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <json.hpp>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include "wiringSerial.h"

#include "controllerlogic.hpp"

using json = nlohmann::json;

struct beaconData {
  float temperature;
  float pressure;
  float humidity;
  float Rx;
  float Ry;
  float Rz;
  int detect;
  time_t timestamp;
};

class RaspberryMaster {

    public:
        RaspberryMaster();
        ~RaspberryMaster();
        void receiveDataFromSlave();
        void changeFormatToJSON(beaconData data, json& jsonData);
        void sendDataToServer(json jsonData, const char* serverIP, int port);
    
    private:
        ControllerLogic *servomotors;

};

#endif