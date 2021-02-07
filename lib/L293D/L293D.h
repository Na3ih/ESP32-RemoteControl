/**
* The file contains definitions of variables and functions used to control the L293D engine driver.
*/

#pragma once

#include "driver/gpio.h"

/**
 * L293D module outputs directions.
 */ 
typedef enum L293D_OUTPUT_DIRECTION {
	L293D_OUTPUT_DIRECTION_LEFT,
	L293D_OUTPUT_DIRECTION_RIGHT,
} L293D_OUTPUT_DIRECTION;

/**
 * Structure containing the gpios used to controll L293D module.
 */ 
struct L293D
{
	const gpio_num_t IN1;
	const gpio_num_t IN2;
	const gpio_num_t ENA12; ///< PWM
	const gpio_num_t IN3;
	const gpio_num_t IN4;
	const gpio_num_t ENA34; ///< PWM
};

/**
 * L293D module outputs. 
 */ 
typedef enum L293D_OUTPUT {
	L293D_OUTPUT_12,
	L293D_OUTPUT_34
} L293D_OUTPUT;

/**
 * Configuration of module control pins.
 * @param motorDriver Structure containing the module pinout.  
 * TODO: configure ENA pins as pwm
 */
void gpioConfig (struct L293D * motorDriver);

/**
 * Set output to neutral ("neutral gear").
 * @param motorDriver Structure containing the module pinout.  
 * @param output Output we want to use.
 */ 
void L293D_outputStop(struct L293D * motorDriver, L293D_OUTPUT output);

/**
 * Locks the output engine in a given position
 * @param motorDriver Structure containing the module pinout.  
 * @param output Output we want to use.
 */ 
void L293D_outputBrake(struct L293D * motorDriver, L293D_OUTPUT output);

/**
 * Starts the engine at full speed in a given direction.
 * @param motorDriver Structure containing the module pinout.  
 * @param output Output we want to use.
 * @param direction Desired direction of rotation.
 * @param speed TODO: VARIABLE SPEED 
 */
void L293D_setOutput(struct L293D * motorDriver, L293D_OUTPUT output, L293D_OUTPUT_DIRECTION direction, uint8_t speed);
