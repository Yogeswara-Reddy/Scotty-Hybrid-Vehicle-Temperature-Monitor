#ifndef NEXTION_H
#define NEXTION_H

#include "stm32f1xx_hal.h"

#define NEXTION_MOTOR_COMPONENT      "motorTemp"
#define NEXTION_BATTERY_COMPONENT    "battTemp"
#define NEXTION_MOTOR_WARN           "motorWarn"
#define NEXTION_BATTERY_WARN         "battWarn"

#define MOTOR_TEMP_WARNING_LIMIT     140.0f
#define BATTERY_TEMP_WARNING_LIMIT    45.0f

#define NEXTION_COLOR_RED            63488
#define NEXTION_COLOR_GREEN          1024
#define NEXTION_COLOR_WHITE          65535

void Nextion_UpdateDisplay(float motor_temp, float battery_temp);
void Nextion_SendCommand(const char *cmd);

#endif
