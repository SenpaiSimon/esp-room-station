#pragma once

#include <driver/i2c_master.h>

#define GY_21_SCL_PIN 19
#define GY_21_SDA_PIN 18
#define GY_21_I2C_NUM I2C_NUM_0
#define GY_21_ADDR    0x40

#define GY_21_TEMP_REG 0xF3
#define GY_21_HUMID_REG 0xF5