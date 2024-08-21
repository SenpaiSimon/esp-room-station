#include "main.h"

void app_main(void) {
    
    static const char *TAG = "MAIN";

    gy_meassurements_t meassurements;

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

    // while(true) {
    //     meassurements = gy21_readAll();
        
    //     ESP_LOGI(TAG, "temp: %.2f°C", meassurements.temperature);
    //     ESP_LOGI(TAG, "humid: %.2f", meassurements.humidity);
    //     ESP_LOGI(TAG, "compHumid: %.2f", meassurements.compHumidity);
        
    //     vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);  
    // }
}