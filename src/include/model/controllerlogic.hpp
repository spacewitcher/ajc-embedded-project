/**
* @file controllerlogic.hpp
* @author Georges Schuhl
* @author Nicolas Chataignon
* @author Houssein Mariam
* @brief This file contains the class definition for ControllerLogic
* @version 1.0
* @date 17 january 2023
*/

#ifndef	__CONTROLLERLOGIC_HPP__
#define	__CONTROLLERLOGIC_HPP__

#include "pipca9685.hpp"
#include <iostream>
#include <chrono>

/**
 * @class ControllerLogic
 * @brief Class for describing the actions that are to be performed by the PCA9685 controller.
 *
 * This class describes the different actions which are to be performed by the PCA9685 controller.
 * It allows to control the positions of the yellow and blue flags using servomotors. 
 * 
 */

class ControllerLogic {

    public:
        /**
         * @brief Default constructor for the ControllerLogic class.
         *
         * This constructor creates an instance of the PiPCA9685 class, initializes the servomotors, and sets the initial positions of the servomotors.
         */
        ControllerLogic();
        /**
         * @brief Default destructor for the ControllerLogic class.
         *
         * This destructor sets the servomotors to the initial position before destroying the object.
         */
        ~ControllerLogic();
        
        /**
         * @brief Method to set the angle of the yellow servomotor
         *
         * @param angle The angle to set the servomotor to
         */
        void setYellowServoPosition(int angle);

        /**
         * @brief Method to set the angle of the blue servomotor.
         *
         * @param angle The angle to set the servomotor to.
         */
        void setBlueServoPosition(int angle);

        /**
         * @brief Method to control the movement of the yellow servomotor when an object is detected.
         *
         */
        void objectDetected();

        /**
         * @brief Method to control the movement of the blue servomotor when data is detected.
         *
         */
        void dataDetected();

        /**
         * @brief Method to control the movement of the blue servomotor when data is transferred.
         *
         */
        void dataTransferred();
    
    private:
        /**
         * @brief PiPCA9685 object.
         *
         */
        PiPCA9685 *servoController;
        /**
         * @brief Current position of the yellow flag initialized to 0 degrees.
         *
         */
        int yellowServoPosition = 0;
        /**
         * @brief Current position of the blue flag initialized to 180 degrees.
         *
         */
        int blueServoPosition = 180;
};

#endif