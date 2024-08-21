#pragma once

#include "config.h"
#include "gy_21/registers.h"
#include "gy_21/types.h"

#include <driver/i2c_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void gy21_init(gy_user_config_t config);

float gy21_readTemp();
float gy21_readHumid();
float gy21_readCompensatedHumid();
gy_meassurements_t gy21_readAll();

esp_err_t gy21_setConfig(gy_user_config_t config);

