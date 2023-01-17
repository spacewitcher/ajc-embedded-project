#include "raspberrymaster.hpp"
#include "wiringSerial.h"

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

    serialFlush(fd); // clear buffer in case there's already data before 1st read

    beaconData data;
    json jsonData = {};

    while(1)

    {
        serialPuts(fd, "p"); // Send confirmation back to the slave

        sleep(5);

        char* data_ptr = (char*)&data;
        for(int i=0; i< (int)sizeof(beaconData); i++) {
        *(data_ptr++) = serialGetchar(fd);
        }

        servomotors->dataDetected();

        if(data.detect == 1)
        {
            servomotors->objectDetected();
        }

        changeFormatToJSON(data, jsonData);
        std::cout << jsonData.dump() << std::endl;

        serialPuts(fd, "A"); // Send confirmation back to the slave
        
        servomotors->dataTransferred();

        sendDataToServer(jsonData, "135.125.14.131", 5009);

    }

    serialClose(fd);
}

void RaspberryMaster::changeFormatToJSON(beaconData data, json &jsonData)
{
 
    jsonData["timestamp"] = data.timestamp;
    jsonData["BME280"]["temperature"] = data.temperature;
    jsonData["BME280"]["pressure"] = data.pressure;
    jsonData["BME280"]["humidity"] = data.humidity;
    jsonData["GY521"]["Rx"] = data.Rx;
    jsonData["GY521"]["Ry"] = data.Ry;
    jsonData["GY521"]["Rz"] = data.Rz;
    jsonData["HC-SR501"]["presence"] = data.detect;
}

void RaspberryMaster::sendDataToServer(json jsonData, const char* serverIP, int port)
{
    int sockfd;
    struct sockaddr_in servaddr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error: Failed to create socket" << std::endl;
        return;
    }

    // Set server address
    memset(&servaddr, '\0', sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = port;
    servaddr.sin_addr.s_addr= inet_addr(serverIP);

    // Connect to server
    int connectToServer = connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

    if (connectToServer < 0) {
        std::cerr << "Error: Failed to connect to server" << std::endl;
        return;
    }
    else {
        std::cout << "Successfully connected to the server" << std::endl;
    }
    
    // Send JSON data to server
    std::string jsonString = jsonData.dump();
    int writeJSON = write(sockfd, jsonString.c_str(), jsonString.length());

    if (writeJSON < 0) {
        std::cerr << "Error: Failed to send JSON data to server" << std::endl;
    } else {
        std::cout << "Sent JSON data to server: " << jsonString << std::endl;
    }

    // Print contents received from server
    char buffer[1024];
    int n = read(sockfd, buffer, sizeof(buffer));
    if (n < 0) {
        std::cerr << "Error: Failed to receive data from server" << std::endl;
    } else {
        buffer[n] = '\0';
        std::cout << "Received from server: " << buffer << std::endl;
    }

    // Close socket
    close(sockfd);
};

