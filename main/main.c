#include "main.h"

void app_main(void) {
    
    static const char *TAG = "MAIN";

    gy_user_config_t config = {
        .bits = {
            .RES_MSB = false,
            .BATTERY = false,
            .HEATER = false,
            .NO_OTP_RELOAD = true,
            .RES_LSB = false,
        }
    };

    gy21_init(config);
    wifiConnect();
    start_webserver();
}