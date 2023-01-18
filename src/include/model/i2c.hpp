/**
* @file qi2c.hpp
* @author manfredipist <https://github.com/manfredipist/QI2CProtocol>
* @brief This file contains the class definition for QI2C
* @version 1.0
* @date 17 january 2023
*/

#ifndef I2C_HPP
#define I2C_HPP

#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/i2c-dev.h>

/**
 * @class I2C
 * @brief Class for controlling the I2C bus
 *
 * This class provides an interface for controlling I2C bus
 * using the Raspberry Pi.
 * 
 */
class I2C
{
public:
    /**
     * @brief Constructor for the QI2C class
     * @param i2c_bus I2C bus number
     * @param i2c_address I2C address of the device
     */
    I2C(const uint8_t &i2c_bus, const uint8_t &i2c_address);
     /**
     * @brief Destructor for the QI2C class
     */
    ~I2C();

     /**
     * @brief Gets the file descriptor of the I2C device
     * @return File descriptor of the I2C device
     */
    int getFileDescriptor(){return fd;}
    
    /**
     * @brief Initializes the I2C bus 
     */
    void i2cInit();
    /**
     * @brief Closes the i2c bus 
     */
    void i2cClose();
     /**
     * @brief Read bit from 8 bit register
     * @param registerAddress The register address
     * @param bitNumber The bit number
     * @return The read bit
     */
    uint8_t readBit8(uint8_t registerAddress, uint8_t bitNumber);
     /**
     * @brief Read bit from 16 bit register
     * @param registerAddress The register address
     * @param bitNumber The bit number
     * @return The read bit
     */
    uint8_t readBit16(uint16_t registerAddress, uint8_t bitNumber);
     /**
     * @brief Read consecutive bits from 8 bit register
     * @param registerAddress The register address
     * @param bitStart The bit start
     * @param length The number of bits to read
     * @return The read bits
     */
    uint8_t readBits8(uint8_t registerAddress, uint8_t bitStart, uint8_t length);
      /**
     * @brief Read consecutive bits from 16 bit register
     * @param registerAddress The register address
     * @param bitStart The bit start
     * @param length The number of bits to read
     * @return The read bits
     */
    uint8_t readBits16(uint16_t registerAddress, uint8_t bitStart, uint8_t length);
    /**
     * @brief Read a byte from 8 bit register
     * @param registerAddress The register address
     * @return The read byte
     */
    uint8_t readByte8(uint8_t registerAddress);
     /**
     * @brief Read a byte from 16 bit register
     * @param registerAddress The register address
     * @return The read byte
     */
    uint8_t readByte16(uint16_t registerAddress);
    /**
     * @brief Read consecutive bytes from 8 bit register
     * @param registerAddress The register address
     * @param length The number of bytes to read
     * @param data The read bytes
     */
    void readBytes8(uint8_t registerAddress, uint8_t length, uint8_t *data);
    /**
     * @brief Read consecutive bytes from 16 bit register
     * @param registerAddress The register address
     * @param length The number of bytes to read
     * @param data The read bytes
     */
    void readBytes16(uint16_t registerAddress, uint8_t length, uint8_t *data);
    /**
     * @brief Read 2 bytes as a word from 8 bit register
     * @param registerAddress The register address
     * @return The read word
     */
    uint16_t readWord8(uint8_t registerAddress);
     /**
     * @brief Read 2 bytes as a word from 16 bit register
     * @param registerAddress The register address
     * @return The read word
     */
    uint16_t readWord16(uint16_t registerAddress);
    /**
     * @brief Read 2 bytes as a word from 8 bit register and swap the byte order
     * @param registerAddress The register address
     * @return The read word
     */
    uint16_t readWord8_2c(uint8_t registerAddress);
    /**
     * @brief Read 2 bytes as a word from 16 bit register and swap the byte order
     * @param registerAddress The register address
     * @return The read word
     */
    uint16_t readWord16_2c(uint16_t registerAddress);
     /**
     * @brief Read 4 bytes as a double word from 16 bit register
     * @param registerAddress The register address
     * @return The read double word
     */
    uint32_t readDoubleWord16(uint16_t registerAddress);

    /**
     * @brief Write a bit to 8 bit register
     * @param registerAddress The register address
     * @param bitNumber The bit number
     * @param data The data to write
     * @return True if the operation was successful, false otherwise
     */
    bool writeBit8(uint8_t registerAddress, uint8_t bitNumber, uint8_t data);
     /**
     * @brief Write a bit to 16 bit register
     * @param registerAddress The register address
     * @param bitNumber The bit number
     * @param data The data to write
     * @return True if the operation was successful, false otherwise
     */
    bool writeBit16(uint16_t registerAddress, uint8_t bitNumber, uint8_t data);
    /**
     * @brief Write consecutive bits to 8 bit register
     * @param registerAddress The register address
     * @param bitStart The bit start
     * @param lenght The number of bits to write
     * @param data The data to write
     * @return True if the operation was successful, false otherwise
     */
    bool writeBits8(uint8_t registerAddress, uint8_t bitStart, uint8_t lenght, uint8_t data);
    /**
     * @brief Write consecutive bits to 16 bit register
     * @param registerAddress The register address
     * @param bitStart The bit start
     * @param lenght The number of bits to write
     * @param data The data to write
     * @return True if the operation was successful, false otherwise
     */
    bool writeBits16(uint16_t registerAddress, uint8_t bitStart, uint8_t lenght, uint8_t data);
    /**
     * @brief Write a byte to 8 bit register
     * @param registerAddress The register address
     * @param data The data to write
     * @return True if the operation was successful, false otherwise
     */
    bool writeByte8(uint8_t registerAddress, uint8_t data);
    /**
     * @brief Write a byte to 16 bit register
     * @param registerAddress The register address
     * @param data The data to write
     * @return True if the operation was successful, false otherwise
     */
    bool writeByte16(uint16_t registerAddress, uint8_t data);
     /**
     * @brief Write consecutive bytes to 8 bit register
     * @param registerAddress The register address
     * @param lenght The number of bytes to write
     * @param data The data to write
     * @return True if the operation was successful, false otherwise
     */
    bool writeBytes8(uint8_t registerAddress, uint8_t lenght, uint8_t *data);
      /**
     * @brief Write consecutive bytes to 16 bit register
     * @param registerAddress The register address
     * @param lenght The number of bytes to write
     * @param data The data to write
     * @return True if the operation was successful, false otherwise
     */
    bool writeBytes16(uint16_t registerAddress, uint8_t lenght, uint8_t *data);
     /**
     * @brief Write 2 bytes as a word to 8 bit register
     * @param registerAddress The register address
     * @param data The data to write
     * @return True if the operation was successful, false otherwise
     */
    bool writeWord8(uint8_t registerAddress, uint16_t data);
    /**
     * @brief Write 2 bytes as a word to 16 bit register
     * @param registerAddress The register address
     * @param data The data to write
     * @return True if the operation was successful, false otherwise
     */
    bool writeWord16(uint16_t registerAddress, uint16_t data);
    /**
     * @brief Write 4 bytes as a double word to 16 bit register
     * @param registerAddress The register address
     * @param data The data to write
     * @return True if the operation was successful, false otherwise
     */
    bool writeDoubleWord(uint16_t registerAddress, uint32_t data);

private:
     /**
     * @brief I2C bus number
     */
    const uint8_t i2c_bus = 0x1;
     /**
     * @brief I2C address of the device
     */
    const uint8_t i2c_address;

     /**
     * @brief The generic connection to user's chosen I2C hardware
     */
    int fd; //The generic connection to user's chosen I2C hardware
};

#endif // I2C_HPP
