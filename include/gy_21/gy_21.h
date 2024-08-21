#pragma once

#include "config.h"
#include "gy_21/registers.h"
#include "gy_21/types.h"

#include <driver/i2c_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void gy21_init();
uint16_t gy21_read(int regToRead);
float gy21_readTemp();
float gy21_readHumid();
float gy21_readCompensatedHumid();

