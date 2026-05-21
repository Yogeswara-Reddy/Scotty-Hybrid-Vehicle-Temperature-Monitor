#include "nextion.h"
#include "modbus_rtu.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <string.h>

extern UART_HandleTypeDef huart1;

static const uint8_t NEXTION_END[3] = {0xFF, 0xFF, 0xFF};

void Nextion_SendCommand(const char *cmd)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)cmd, strlen(cmd), HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart1, (uint8_t *)NEXTION_END, 3, HAL_MAX_DELAY);
    HAL_Delay(10);
}

static void Nextion_SetColor(const char *component, uint16_t color)
{
    char cmd_buffer[64];
    snprintf(cmd_buffer, sizeof(cmd_buffer), "%s.pco=%d", component, color);
    Nextion_SendCommand(cmd_buffer);
}

void Nextion_UpdateDisplay(float motor_temp, float battery_temp)
{
    char motor_line[64];
    char battery_line[64];
    char warn_line[64];

    /* ── Motor temperature line ── */
    if (motor_temp == -999.0f)
    {
        snprintf(motor_line, sizeof(motor_line),
                 "%s.txt=\"Motor Temperature : Sensor Error!\"",
                 NEXTION_MOTOR_COMPONENT);
        Nextion_SetColor(NEXTION_MOTOR_COMPONENT, NEXTION_COLOR_RED);
    }
    else if (motor_temp > MOTOR_TEMP_WARNING_LIMIT)
    {
        snprintf(motor_line, sizeof(motor_line),
                 "%s.txt=\"Motor Temperature : %.1f C [!! WARNING !!]\"",
                 NEXTION_MOTOR_COMPONENT, motor_temp);
        Nextion_SetColor(NEXTION_MOTOR_COMPONENT, NEXTION_COLOR_RED);
    }
    else
    {
        snprintf(motor_line, sizeof(motor_line),
                 "%s.txt=\"Motor Temperature : %.1f C\"",
                 NEXTION_MOTOR_COMPONENT, motor_temp);
        Nextion_SetColor(NEXTION_MOTOR_COMPONENT, NEXTION_COLOR_GREEN);
    }
    Nextion_SendCommand(motor_line);

    /* ── Battery temperature line ── */
    if (battery_temp == -999.0f)
    {
        snprintf(battery_line, sizeof(battery_line),
                 "%s.txt=\"Battery Temperature: Sensor Error!\"",
                 NEXTION_BATTERY_COMPONENT);
        Nextion_SetColor(NEXTION_BATTERY_COMPONENT, NEXTION_COLOR_RED);
    }
    else if (battery_temp > BATTERY_TEMP_WARNING_LIMIT)
    {
        snprintf(battery_line, sizeof(battery_line),
                 "%s.txt=\"Battery Temperature: %.1f C [!! WARNING !!]\"",
                 NEXTION_BATTERY_COMPONENT, battery_temp);
        Nextion_SetColor(NEXTION_BATTERY_COMPONENT, NEXTION_COLOR_RED);
    }
    else
    {
        snprintf(battery_line, sizeof(battery_line),
                 "%s.txt=\"Battery Temperature: %.1f C\"",
                 NEXTION_BATTERY_COMPONENT, battery_temp);
        Nextion_SetColor(NEXTION_BATTERY_COMPONENT, NEXTION_COLOR_GREEN);
    }
    Nextion_SendCommand(battery_line);

    /* ── Warning line ── */
    if (motor_temp > MOTOR_TEMP_WARNING_LIMIT)
    {
        snprintf(warn_line, sizeof(warn_line),
                 "%s.txt=\"*** MOTOR OVERHEATING! CHECK IMMEDIATELY ***\"",
                 NEXTION_MOTOR_WARN);
        Nextion_SetColor(NEXTION_MOTOR_WARN, NEXTION_COLOR_RED);
    }
    else if (battery_temp > BATTERY_TEMP_WARNING_LIMIT)
    {
        snprintf(warn_line, sizeof(warn_line),
                 "%s.txt=\"*** BATTERY OVERHEATING! CHECK IMMEDIATELY ***\"",
                 NEXTION_BATTERY_WARN);
        Nextion_SetColor(NEXTION_BATTERY_WARN, NEXTION_COLOR_RED);
    }
    else
    {
        snprintf(warn_line, sizeof(warn_line),
                 "%s.txt=\"\"",
                 NEXTION_MOTOR_WARN);
        Nextion_SendCommand(warn_line);
        snprintf(warn_line, sizeof(warn_line),
                 "%s.txt=\"\"",
                 NEXTION_BATTERY_WARN);
    }
    Nextion_SendCommand(warn_line);

    /* ── Send via Modbus RTU ── */
    Modbus_SendTemperature(MODBUS_ADDR_MOTOR_TEMP,   motor_temp);
    Modbus_SendTemperature(MODBUS_ADDR_BATTERY_TEMP, battery_temp);
}
