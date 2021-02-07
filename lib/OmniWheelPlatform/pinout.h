/**
 * File contains definitions of GPIO pins used to control the L293D engine driver.
 */ 

#pragma once

#include "driver/gpio.h"
#include "L293D.h"

const gpio_num_t L293D_DRIVER1_PIN_IN1 = GPIO_NUM_4;
const gpio_num_t L293D_DRIVER1_PIN_IN2 = GPIO_NUM_2;
const gpio_num_t L293D_DRIVER1_PIN_IN3 = GPIO_NUM_14;
const gpio_num_t L293D_DRIVER1_PIN_IN4 = GPIO_NUM_12;
const gpio_num_t L293D_DRIVER1_PIN_ENA12 = GPIO_NUM_16;
const gpio_num_t L293D_DRIVER1_PIN_ENA34 = GPIO_NUM_13;

const gpio_num_t L293D_DRIVER2_PIN_IN1 = GPIO_NUM_19;
const gpio_num_t L293D_DRIVER2_PIN_IN2 = GPIO_NUM_21;
const gpio_num_t L293D_DRIVER2_PIN_IN3 = GPIO_NUM_33;
const gpio_num_t L293D_DRIVER2_PIN_IN4 = GPIO_NUM_25;
const gpio_num_t L293D_DRIVER2_PIN_ENA12 = GPIO_NUM_18;
const gpio_num_t L293D_DRIVER2_PIN_ENA34 = GPIO_NUM_32;