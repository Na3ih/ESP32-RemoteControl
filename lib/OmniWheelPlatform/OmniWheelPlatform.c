#include "OmniWheelPlatform.h"
#include "pinout.h"

struct L293D motorDriver1 = {
	L293D_DRIVER1_PIN_IN1,
	L293D_DRIVER1_PIN_IN2,
	L293D_DRIVER1_PIN_ENA12,
	
	L293D_DRIVER1_PIN_IN3,
	L293D_DRIVER1_PIN_IN4,
	L293D_DRIVER1_PIN_ENA34
};	

struct L293D motorDriver2 = {
	L293D_DRIVER2_PIN_IN1,
	L293D_DRIVER2_PIN_IN2,
	L293D_DRIVER2_PIN_ENA12,
	
	L293D_DRIVER2_PIN_IN3,
	L293D_DRIVER2_PIN_IN4,
	L293D_DRIVER2_PIN_ENA34	
};

void stop()
{
	L293D_outputStop(&motorDriver1, L293D_OUTPUT_12);
	L293D_outputStop(&motorDriver1, L293D_OUTPUT_34);
	L293D_outputStop(&motorDriver2, L293D_OUTPUT_12);
	L293D_outputStop(&motorDriver2, L293D_OUTPUT_34);
}

void brake() {
	L293D_outputBrake(&motorDriver1, L293D_OUTPUT_12);
	L293D_outputBrake(&motorDriver1, L293D_OUTPUT_34);
	L293D_outputBrake(&motorDriver2, L293D_OUTPUT_12);
	L293D_outputBrake(&motorDriver2, L293D_OUTPUT_34);
}

void move(MOVE_DIRECTION direction, uint8_t speed)
{

	switch (direction) {
		case MOVE_DIRECTION_FORWARD:
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_LEFT, speed);
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_LEFT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_LEFT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_LEFT, speed);
			break;
		case MOVE_DIRECTION_BACKWARD:
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			break;
		case MOVE_DIRECTION_LEFT:
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_LEFT, speed);
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_LEFT, speed);
			break;
		case MOVE_DIRECTION_RIGHT:
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_LEFT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_LEFT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			break;
		case MOVE_DIRECTION_FORWARD_LEFT:
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_LEFT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_LEFT, speed);
			break;
		case MOVE_DIRECTION_FORWARD_RIGHT:
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_LEFT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_LEFT, speed);
			break;
		case MOVE_DIRECTION_BACKWARD_RIGHT:
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			break;
		case MOVE_DIRECTION_BACKWARD_LEFT:
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			break;
		case MOVE_DIRECTION_TURN_RIGHT:
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_LEFT, speed);
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_LEFT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			break;
		case MOVE_DIRECTION_TURN_LEFT:
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			L293D_setOutput(&motorDriver1, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_LEFT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_12, L293D_OUTPUT_DIRECTION_RIGHT, speed);
			L293D_setOutput(&motorDriver2, L293D_OUTPUT_34, L293D_OUTPUT_DIRECTION_LEFT, speed);
			break;
		break;
		default:
			stop();
			break;
	}
}
