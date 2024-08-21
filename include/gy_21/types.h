#pragma once

typedef union gy_user_config {
    unsigned int data;
    struct {
        bool RES_MSB : 1;
        bool BATTERY : 1;
        int : 3;
        bool HEATER : 1;
        bool NO_OTP_RELOAD : 1;
        bool RES_LSB : 1;
    } bits;
} gy_user_config_t;
