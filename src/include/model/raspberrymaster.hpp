/**
 * @file raspberrymaster.hpp
 * @author Georges Schuhl
 * @brief This file contains the declaration of the RaspberryMaster class and the beaconData struct.
 *        The RaspberryMaster class is used for communication between the Raspberry Pi and the slave device.
 *        The beaconData struct contains data received from the slave device, such as temperature, pressure, humidity, etc.
 * @version 1.0
 * @date 17 january 2023
 */

#ifndef	__RASPBERRYMASTER_HPP__
#define	__RASPBERRYMASTER_HPP__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <json.hpp>
#include <iostream>
#include <termios.h>
#include "wiringSerial.h"
#include <thread>
#include <mutex>
#include <condition_variable>

#include "controllerlogic.hpp"

using json = nlohmann::json;

/**
 * @brief The beaconData struct contains data received from the slave device, such as temperature, pressure, humidity, x, y, z
 * axes positions, detection status and a timestamp.
 */
struct beaconData {
    /** temperature in degree celsius */
    float temperature;
    /** pressure in pascal*/
    float pressure;
    /** humidity in percentage*/
    float humidity;
    /** x axis rotation */
    float Rx;
    /** y axis rotation */
    float Ry;
    /** z axis rotation */
    float Rz;
    /** detection status*/
    int detect;
    /** timestamp*/
    time_t timestamp;
};

/**
 * @class RaspberryMaster
 * @brief The RaspberryMaster class is used for communication between the Master device, the slave device and the TCP remote server.
 *        It contains methods for receiving data from the slave device, changing the format of the data to JSON, and sending the data to a server.
 *        It also dictates when the servocontroller should perform its actions.
 */
class RaspberryMaster {

    public:
        /**
         * @brief Constructor for the RaspberryMaster class.
         */
        RaspberryMaster();

        /**
         * @brief Destructor for the RaspberryMaster class.
         */
        ~RaspberryMaster();

        /**
         * @brief Method for receiving data from the slave device.
         */
        void receiveDataFromSlave();

        /**
         * @brief Method for creating a thread for the object detection.
         * @param data The data received from the slave device in the form of a beaconData struct.
         */
        void changeFormatToJSON(beaconData data, json& jsonData);

        /**
         * @brief Method for sending the data to a server.
         * @param jsonData The data in JSON format.
         * @param serverIP The IP address of the server.
         * @param port The port number that the data will be sent to.
         */
        void sendDataToServer(std::vector<json> jsonDataBuffer, std::string serverIP, int port);
    
    private:
        /**
         * @brief Pointer to the ControllerLogic class.
         */
        ControllerLogic *servomotors;
         /**
         * @brief Mutex variable to protect the JSON data buffer in multithreading.
         */
        std::mutex jsonDataBuffer_mutex;

};

#endif
