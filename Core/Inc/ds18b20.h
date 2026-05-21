#ifndef DS18B20_H
#define DS18B20_H

#include "stm32f1xx_hal.h"

#define MOTOR_SENSOR_PIN       GPIO_PIN_0
#define BATTERY_SENSOR_PIN     GPIO_PIN_1
#define SENSOR_GPIO_PORT       GPIOA

#define DS18B20_SKIP_ROM        0xCC
#define DS18B20_CONVERT_T       0x44
#define DS18B20_READ_SCRATCHPAD 0xBE

float DS18B20_ReadTemperature(uint16_t sensor_pin);

#endif
