/**
* @file pipca9685.hpp
* @author Georges Schuhl
* @author Nicolas Chataignon
* @author Houssein Mariam
* @author manfredipist <https://github.com/manfredipist/QI2CProtocol>
* @brief This file contains the class definition for PiPCA9685
* @version 1.0
* @date 17 january 2023
*
*/

#ifndef PIPCA9685_HPP
#define PIPCA9685_HPP

#include "i2c.hpp"

/** @brief Register address for Mode 1 */
#define MODE1			0x00
/** @brief Register address for Mode 2 */
#define MODE2			0x01
/** @brief Register address for Subaddress 1 */
#define SUBADR1			0x02
/** @brief Register address for Subaddress 2 */
#define SUBADR2			0x03
/** @brief Register address for Subaddress 3 */
#define SUBADR3			0x04
/** @brief Register address for Prescale */
#define PRESCALE		0xFE
/** @brief Register address for LED 0 on low byte */
#define LED0_ON_L		0x06
/** @brief Register address for LED 0 on high byte */
#define LED0_ON_H		0x07
/** @brief Register address for LED 0 off low byte */
#define LED0_OFF_L		0x08
/** @brief Register address for LED 0 off high byte */
#define LED0_OFF_H		0x09
/** @brief Register address for all LED on low byte */
#define ALL_LED_ON_L    0xFA
/** @brief Register address for all LED on high byte */
#define ALL_LED_ON_H	0xFB
/** @brief Register address for all LED off low byte */
#define ALL_LED_OFF_L	0xFC
/** @brief Register address for all LED off high byte */
#define ALL_LED_OFF_H	0xFD
/** @brief Bit for restarting */
#define RESTART			0x80
/** @brief Bit for sleeping */
#define SLEEP			0x10
/** @brief Bit for all call */
#define ALLCALL			0x01
/** @brief Bit for inverting */
#define INVRT			0x10
/** @brief Bit for output driving */
#define OUTDRV			0x04

/** @brief Channel for pan control */
#define PAN			    0
/** @brief Channel for tilt control */
#define TILT			1
/** @brief PWM frequency */
#define FREQUENCY		50
/** @brief Clock frequency */
#define CLOCKFREQ		25000000
/** @brief Pan offset */
#define PANOFFSET		1
/** @brief Pan scale */
#define PANSCALE		1.4
/** @brief Tilt offset */
#define TILTOFFSET		30
/** @brief Tilt scale */
#define TILTSCALE		1.43
/** @brief Maximum pan angle */
#define PANMAX			270
/** @brief Minimum pan angle */
#define PANMIN			90
/** @brief Maximum tilt angle */
#define TILTMAX			90
/** @brief Minimum tilt angle */
#define TILTMIN			-45

/**
 * @class PiPCA9685
 * @brief Class for controlling the PCA9685 PWM chip
 *
 * This class provides an interface for controlling the PCA9685 PWM chip
 * using the I2C bus on a Raspberry Pi. It allows to change the positions
 * of the servomotors based on the desired angle (in degrees).
 * 
 */

class PiPCA9685
{
public:
    /**
     * @brief Constructor for the PiPCA9685 class
     * @param i2c_bus I2C bus number
     * @param i2c_address I2C address of the PCA9685 chip
     */
    explicit PiPCA9685(uint8_t i2c_bus, uint8_t i2c_address);
    /**
     * @brief Destructor for the PiPCA9685 class
     * 
     */
    ~PiPCA9685();

public:
    /**
     * @brief Initialize the PCA9685 chip
     */
    void initialize();
    /**
     * @brief Set the PWM frequency for all channels
     * @param frequency PWM frequency in Hz
     */
    void setPwmFrequency(uint16_t frequency);
    /**
     * @brief Set the PWM duty cycle for a specific channel
     * @param channel PWM channel (0-15)
     * @param on Duty cycle on time in ticks
     * @param off Duty cycle off time in ticks
     */
    void setPwm(uint8_t channel, uint16_t on, uint16_t off);
    /**
     * @brief Set the PWM duty cycle for all channels
     * @param on Duty cycle on time in ticks
     * @param off Duty cycle off time in ticks
     */
    void setAllPwm(uint16_t on, uint16_t off);
    /**
     * @brief Move the servo to the specified degree
     * @param channel PWM channel (0-15)
     * @param deg Degrees to move
     */
    void move(uint8_t channel , int deg);

private:
    /**
     * @brief I2C interface object
     */
    I2C *i2c;

    /**
     * @brief I2C bus number
     */
    const uint8_t i2c_bus;
    /**
     * @brief I2C address of the PCA9685 chip
     */
    const uint8_t i2c_address;
};

#endif // PIPCA9685_HPP
