#pragma once

#include "config.h"
#include <driver/i2c.h>
#include "esp_log.h"

void gy21_init();
uint16_t gy21_read(int regToRead);
float gy21_readTemp();
float gy21_readHumid();

