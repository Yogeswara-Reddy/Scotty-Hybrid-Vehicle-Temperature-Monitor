#ifndef MODBUS_RTU_H
#define MODBUS_RTU_H

#include "stm32f1xx_hal.h"

#define RS485_DE_RE_PIN      GPIO_PIN_4
#define RS485_DE_RE_PORT     GPIOA

#define MODBUS_ADDR_MOTOR_TEMP    0x01
#define MODBUS_ADDR_BATTERY_TEMP  0x02
#define MODBUS_FUNC_WRITE         0x10

void     Modbus_SendTemperature(uint8_t device_addr, float temperature);
uint16_t Modbus_CRC16(uint8_t *data, uint16_t length);

#endif
