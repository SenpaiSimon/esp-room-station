#include "main.h"

void app_main(void) {
    
    static const char *TAG = "MAIN";

    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_LOGI(TAG, "NVS INIT Done");

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
    ESP_LOGI(TAG, "GY21 INIT Done");
    wifiConnect();
    ESP_LOGI(TAG, "WIFI INIT Done");
    start_webserver();
    ESP_LOGI(TAG, "WEBSERVER INIT Done");
}