#include "main.h"

void app_main(void) {
    
    static const char *TAG = "MAIN";
    float temp;
    float humid;
    float compHumid;

    gy21_init();
    while(true) {
        temp = gy21_readTemp();
        humid = gy21_readHumid();
        compHumid = gy21_readCompensatedHumid();
        
        ESP_LOGI(TAG, "temp: %.2f°C", temp);
        ESP_LOGI(TAG, "humid: %.2f", humid);
        ESP_LOGI(TAG, "compHumid: %.2f", compHumid);
        
        vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);  
    }
}