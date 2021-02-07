/**
 * File contains definitions of variables and functions used to control 
 * the multidirectional platform using 4 independently controlled omnidirectional wheels.
 */ 

#pragma once
#include <L293D.h>

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