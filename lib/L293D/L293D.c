#include "driver/gpio.h"
#include "L293D.h"

/**
 * It selects the appropriate pin numbers based on the input parameters and places them in the vector.
 * @param motorDriver Structure containing the module pinout.  
 * @param output Output we want to use.
 * @param gpios Vector to enter pin numbers.  
 */ 
static void getControlLines(struct L293D * motorDriver, L293D_OUTPUT output, gpio_num_t gpios[2])
{
		gpio_num_t gpio1 = 0;
		gpio_num_t gpio2 = 0;
		
		switch (output) {
		case L293D_OUTPUT_12:
			gpio1 = motorDriver->IN1;
			gpio2 = motorDriver->IN2;
			break;
			case L293D_OUTPUT_34:
			gpio1 = motorDriver->IN3;
			gpio2 = motorDriver->IN4;
			break;
	}
	gpios[0] = gpio1;
	gpios[1] = gpio2;
}

void L293D_outputStop(struct L293D * motorDriver, L293D_OUTPUT output)
{
	gpio_num_t gpios[2];
	getControlLines(motorDriver, output, gpios);
	gpio_set_level(gpios[0], 0);
	gpio_set_level(gpios[1], 0);
}

void L293D_outputBrake(struct L293D * motorDriver, L293D_OUTPUT output)
{
	gpio_num_t gpios[2];
	getControlLines(motorDriver, output, gpios);
	gpio_set_level(gpios[0], 1);
	gpio_set_level(gpios[1], 1);
}

void L293D_setOutput(struct L293D * motorDriver, L293D_OUTPUT output, L293D_OUTPUT_DIRECTION direction, uint8_t speed)
{
	gpio_num_t gpios[2];
	getControlLines(motorDriver, output, gpios);

	switch (direction) {
		case L293D_OUTPUT_DIRECTION_LEFT:
			gpio_set_level(gpios[0], 1);
			gpio_set_level(gpios[1], 0);
			break;
		case L293D_OUTPUT_DIRECTION_RIGHT:
			gpio_set_level(gpios[0], 0);
			gpio_set_level(gpios[1], 1);
			break;
		default:
			gpio_set_level(gpios[0], 0);
			gpio_set_level(gpios[1], 0);
			break;
	}

	///TODO: ENA pins -> PWM -> speed
	gpio_set_level(motorDriver->ENA12, 1);
	gpio_set_level(motorDriver->ENA34, 1);
}

void gpioConfig (struct L293D * motorDriver) {
  gpio_num_t gpioMap[] = {  motorDriver->IN1,
                            motorDriver->IN2,
                            motorDriver->IN3,
                            motorDriver->IN4,
                            motorDriver->ENA12,
                            motorDriver->ENA34
  };

  for (uint8_t i = 0; i < (sizeof(gpioMap) / sizeof(gpio_num_t)); i++) {
      gpio_pad_select_gpio(gpioMap[i]);
      gpio_set_direction(gpioMap[i], GPIO_MODE_OUTPUT);
      gpio_set_level(gpioMap[i], 0);
  }
} 