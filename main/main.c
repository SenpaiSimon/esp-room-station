#include "main.h"

void app_main(void) {
    
    gy21_init();
    while(true) {
        gy21_readTemp();
        gy21_readHumid();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}