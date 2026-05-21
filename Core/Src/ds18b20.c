#include "ds18b20.h"
#include "stm32f1xx_hal.h"

static void delay_us(uint16_t us)
{
    uint32_t count = us * 8;
    while(count--);
}

static void Set_Pin_Output(uint16_t pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin   = pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SENSOR_GPIO_PORT, &GPIO_InitStruct);
}

static void Set_Pin_Input(uint16_t pin)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin  = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(SENSOR_GPIO_PORT, &GPIO_InitStruct);
}

static uint8_t OneWire_Reset(uint16_t pin)
{
    uint8_t presence = 0;
    Set_Pin_Output(pin);
    HAL_GPIO_WritePin(SENSOR_GPIO_PORT, pin, GPIO_PIN_RESET);
    delay_us(480);
    Set_Pin_Input(pin);
    delay_us(80);
    if (HAL_GPIO_ReadPin(SENSOR_GPIO_PORT, pin) == GPIO_PIN_RESET)
    {
        presence = 1;
    }
    delay_us(400);
    return presence;
}

static void OneWire_WriteByte(uint16_t pin, uint8_t byte)
{
    for (int i = 0; i < 8; i++)
    {
        Set_Pin_Output(pin);
        HAL_GPIO_WritePin(SENSOR_GPIO_PORT, pin, GPIO_PIN_RESET);
        delay_us(2);
        if (byte & (1 << i))
        {
            HAL_GPIO_WritePin(SENSOR_GPIO_PORT, pin, GPIO_PIN_SET);
        }
        delay_us(60);
        Set_Pin_Input(pin);
        delay_us(2);
    }
}

static uint8_t OneWire_ReadByte(uint16_t pin)
{
    uint8_t byte = 0;
    for (int i = 0; i < 8; i++)
    {
        Set_Pin_Output(pin);
        HAL_GPIO_WritePin(SENSOR_GPIO_PORT, pin, GPIO_PIN_RESET);
        delay_us(2);
        Set_Pin_Input(pin);
        delay_us(10);
        if (HAL_GPIO_ReadPin(SENSOR_GPIO_PORT, pin) == GPIO_PIN_SET)
        {
            byte |= (1 << i);
        }
        delay_us(50);
    }
    return byte;
}

float DS18B20_ReadTemperature(uint16_t sensor_pin)
{
    uint8_t byte1, byte2;
    int16_t raw;
    float temperature;

    if (!OneWire_Reset(sensor_pin))
    {
        return -999.0f;
    }

    OneWire_WriteByte(sensor_pin, DS18B20_SKIP_ROM);
    OneWire_WriteByte(sensor_pin, DS18B20_CONVERT_T);
    HAL_Delay(750);

    OneWire_Reset(sensor_pin);
    OneWire_WriteByte(sensor_pin, DS18B20_SKIP_ROM);
    OneWire_WriteByte(sensor_pin, DS18B20_READ_SCRATCHPAD);

    byte1 = OneWire_ReadByte(sensor_pin);
    byte2 = OneWire_ReadByte(sensor_pin);

    raw = (int16_t)((byte2 << 8) | byte1);
    temperature = (float)raw / 16.0f;

    return temperature;
}
