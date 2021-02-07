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
void L293D_setOutput(struct L293D * motorDriver, L293D_OUTPUT output, L293D_OUTPUT_DIRECTION direction, uint8_t speed)


// --------------------------------------------- PLATFORM -------------------------------------------------------- //

/**
 * Possible directions of the platform move.
 */ 
typedef enum MOVE_DIRECTION {
	MOVE_DIRECTION_FORWARD,
	MOVE_DIRECTION_BACKWARD,
	MOVE_DIRECTION_LEFT,
	MOVE_DIRECTION_RIGHT,
	MOVE_DIRECTION_FORWARD_LEFT,
	MOVE_DIRECTION_FORWARD_RIGHT,
	MOVE_DIRECTION_BACKWARD_RIGHT,
	MOVE_DIRECTION_BACKWARD_LEFT,
	MOVE_DIRECTION_TURN_RIGHT,
	MOVE_DIRECTION_TURN_LEFT
} MOVE_DIRECTION;

/**
 * Drivers declarations.
 */ 
struct L293D motorDriver1;
struct L293D motorDriver2;

/**
 * Moves the platform in the selected direction.
 * @param direction Desired direction of rotation
 * @param speed TODO: VARIABLE SPEED 
 */
void move(MOVE_DIRECTION direction, uint8_t speed);

/**
 * Platform stop = neutral gear (cut off current from engines).
 */ 
void stop();

/**
 * Platform brake - engines blockage.
 */ 
void brake();