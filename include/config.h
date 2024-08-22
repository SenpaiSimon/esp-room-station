#pragma once

#include <driver/i2c_master.h>
#include <esp_wifi.h>

#define GY_21_SCL_PIN 19
#define GY_21_SDA_PIN 18
#define GY_21_I2C_NUM I2C_NUM_0
#define GY_21_TEMP_COEFF -0.15

#define HOSTNAME "esp-room-sens"
#define DEFAULT_LISTEN_INTERVAL 3
#define DEFAULT_BEACON_TIMEOUT 6
#define DEFAULT_PS_MODE WIFI_PS_MIN_MODEM