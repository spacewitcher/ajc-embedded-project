#include "raspberrymaster.hpp"

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
    std::vector<json> jsonDataBuffer; // buffer to store json data
    
    // Initialize the timer
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + std::chrono::seconds(30);

    while(1)

    {
        // Create three threads, one for detecting presence, one for detecting data, one for transferring data
        std::thread presence_detection;
        std::thread data_detection;
        std::thread data_transfer;

        serialPuts(fd, "p"); // Send confirmation back to the slave

        if (serialDataAvail(fd) < 0) continue; // if no data available from slave, continue

        std::this_thread::sleep_for(std::chrono::seconds(5)); // sleep for 5 seconds


        char* data_ptr = (char*)&data;
        for(int i=0; i< (int)sizeof(beaconData); i++) 
        {
            *(data_ptr++) = serialGetchar(fd); // Receiving the data from the slave
        }

        data_detection = std::thread(&ControllerLogic::dataDetected, servomotors); // Data detected, detach thread 1, move blue flag
        data_detection.detach();
        //servomotors->dataDetected();

        if (data.detect == 1)
        {
            presence_detection = std::thread(&ControllerLogic::objectDetected, servomotors); // Object detected, detach thread 2, move yellow flag
            presence_detection.detach();
            //servomotors->objectDetected();
        }
        
        jsonDataBuffer_mutex.lock();
        changeFormatToJSON(data, jsonData);
        jsonDataBuffer_mutex.unlock();

        jsonDataBuffer.push_back(jsonData); // store json data in buffer

        for(auto i : jsonDataBuffer) {
                std::cout << std::endl;
                std::cout << i.dump() << std::endl;
        }

        serialPuts(fd, "A"); // Send confirmation back to the slave

        if (std::chrono::high_resolution_clock::now() > end) { //if a minute passed
            //servomotors->dataTransferred();
            data_transfer = std::thread(&ControllerLogic::dataTransferred, servomotors);// Data is going to be transferred, move blue flag
            data_transfer.detach();
            jsonDataBuffer_mutex.lock();
            sendDataToServer(jsonDataBuffer, "135.125.14.131", 5009);
            jsonDataBuffer_mutex.unlock();
            jsonDataBuffer.clear(); //clear the buffer
            start = std::chrono::high_resolution_clock::now(); // reinitialize the clock
            end = start + std::chrono::seconds(30);
        }
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


void RaspberryMaster::sendDataToServer(std::vector<json> jsonDataBuffer, std::string serverIP, int port)
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
    servaddr.sin_addr.s_addr= inet_addr(serverIP.c_str());

    // Connect to server
    int connectToServer = connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

    if (connectToServer < 0) {
        std::cerr << "Error: Failed to connect to server" << std::endl;
        return;
    }
    else {
        std::cout << "Successfully connected to the server" << std::endl;
    }

    // Convert JSON data buffer to a single string
    json jsonDataToSend;
    jsonDataToSend["data"] = jsonDataBuffer;
    std::string jsonString = jsonDataToSend.dump();

     // Send JSON data to server
    int writeJSON = write(sockfd, jsonString.c_str(), jsonString.length());

    if (writeJSON < 0) {
        std::cerr << "Error: Failed to send JSON data to server" << std::endl;
    } else {
        std::cout << "Sent JSON data to server: " << jsonString << std::endl;
    }

    // Close socket
    close(sockfd);
};


