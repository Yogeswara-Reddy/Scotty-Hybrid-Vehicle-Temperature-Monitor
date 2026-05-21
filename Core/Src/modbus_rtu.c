#include "modbus_rtu.h"
#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart1;

static void RS485_TransmitMode(void)
{
    HAL_GPIO_WritePin(RS485_DE_RE_PORT, RS485_DE_RE_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
}

static void RS485_ReceiveMode(void)
{
    HAL_Delay(2);
    HAL_GPIO_WritePin(RS485_DE_RE_PORT, RS485_DE_RE_PIN, GPIO_PIN_RESET);
}

uint16_t Modbus_CRC16(uint8_t *data, uint16_t length)
{
    uint16_t crc = 0xFFFF;
    for (uint16_t i = 0; i < length; i++)
    {
        crc ^= (uint16_t)data[i];
        for (int j = 0; j < 8; j++)
        {
            if (crc & 0x0001)
            {
                crc = (crc >> 1) ^ 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

void Modbus_SendTemperature(uint8_t device_addr, float temperature)
{
    uint8_t  frame[6];
    uint16_t crc;

    int16_t temp_scaled = (int16_t)(temperature * 10.0f);

    frame[0] = device_addr;
    frame[1] = MODBUS_FUNC_WRITE;
    frame[2] = (temp_scaled >> 8) & 0xFF;
    frame[3] =  temp_scaled       & 0xFF;

    crc      = Modbus_CRC16(frame, 4);
    frame[4] = crc & 0xFF;
    frame[5] = (crc >> 8) & 0xFF;

    RS485_TransmitMode();
    HAL_UART_Transmit(&huart1, frame, 6, HAL_MAX_DELAY);
    RS485_ReceiveMode();
}
