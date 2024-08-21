#pragma once

typedef union gy_user_config {
    unsigned int data;
    struct {
        bool RES_LSB : 1; // starts with LSB
        bool NO_OTP_RELOAD : 1;
        bool HEATER : 1;
        int : 3;
        bool BATTERY : 1;
        bool RES_MSB : 1; // ends with MSB
    } bits;
} gy_user_config_t;

typedef struct gy_meassurements {
    float temperature;
    float humidity;
    float compHumidity;
} gy_meassurements_t;
