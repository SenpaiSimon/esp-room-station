#include "gy_21/gy_21.h"

i2c_config_t conf = {
	.mode = I2C_MODE_MASTER,
	.sda_io_num = GY_21_SDA_PIN,
	.scl_io_num = GY_21_SCL_PIN,
	.sda_pullup_en = GPIO_PULLUP_ENABLE,
	.scl_pullup_en = GPIO_PULLUP_ENABLE,
	.master.clk_speed = 100000,
};

i2c_master_bus_handle_t i2c_handle;

static const char *GY_TAG = "GY21";

void gy21_init() {
    // add the master bus
    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0));
}

uint16_t gy21_read(int regToRead) {
    uint8_t buffer[10] = {0};
    uint8_t reg = regToRead;
    uint8_t maxWait = 30;
    
    esp_err_t ret;
    ret = i2c_master_write_to_device(I2C_NUM_0, GY_21_ADDR, &reg, 1, 100/portTICK_PERIOD_MS);
    if(ret != ESP_OK) {
        ESP_LOGW(GY_TAG, "write failed %x", ret);
    }

    // vTaskDelay(100 / portTICK_PERIOD_MS);
    int wait = 0;
    ret = ESP_FAIL;

    // poll the slave
    while(ret != ESP_OK) {
        ret = i2c_master_read_from_device(I2C_NUM_0, GY_21_ADDR, buffer, 3, 100/portTICK_PERIOD_MS);
        if(ret != ESP_OK) {
            wait++;
            if(wait >= maxWait) {
                break;
            }
            vTaskDelay(1 / portTICK_PERIOD_MS);
        } else {
            break;
        }
    }

    if(ret != ESP_OK) {
        ESP_LOGW(GY_TAG, "read failed %x", ret);
    }

    // discard lower 2 bits
    uint16_t res = buffer[0] << 8 | (buffer[1] ^ 0x02);
    return res;
}

float gy21_readTemp() {
    uint16_t res = gy21_read(GY_21_TEMP_REG);
    float temp = 0.002681274 * (float)res - 46.85;
    ESP_LOGI(GY_TAG, "temp: %.2f°C", temp);
    return temp;
}

float gy21_readHumid() {
    uint16_t res = gy21_read(GY_21_HUMID_REG);
    float temp = 0.001918334 * (float)res - 6;

    // clip top and bottom
    if(temp < 0) {
        temp = 0;
    } else if(temp > 100) {
        temp = 100;
    }
    
    ESP_LOGI(GY_TAG, "humid: %.2f", temp);
    return temp;
}