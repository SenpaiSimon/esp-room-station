#include "gy_21/gy_21.h"

uint16_t gy21_read(int regToRead, int delay);

i2c_master_bus_config_t i2c_bus_config = {
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .i2c_port = I2C_NUM_0,
    .scl_io_num = GY_21_SCL_PIN,
    .sda_io_num = GY_21_SDA_PIN,
    .glitch_ignore_cnt = 7,
    .flags.enable_internal_pullup = true,
};

i2c_master_bus_handle_t i2c_bus_handle;

i2c_device_config_t gy21_dev_conf = {
    .scl_speed_hz = 400 * 1000,
    .device_address = GY_21_ADDR
};

uint8_t temperature_delay;
uint8_t humidity_delay;

static const char *GY_TAG = "GY21";

void gy21_init(gy_user_config_t config) {
    // add the master bus
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_bus_config, &i2c_bus_handle));
    ESP_ERROR_CHECK(gy21_setConfig(config));
}

esp_err_t gy21_setConfig(gy_user_config_t config) {
    esp_err_t ret;
    uint8_t reg = GY_21_WRITE_USER_REG;
    uint8_t buffer[2];
    
    i2c_master_dev_handle_t dev_handle;
    if (i2c_master_bus_add_device(i2c_bus_handle, &gy21_dev_conf, &dev_handle) != ESP_OK) {
        ESP_LOGE(GY_TAG, "Device Bus add failed");
    }

    buffer[0] = reg;
    buffer[1] = config.data;
    ret = i2c_master_transmit(dev_handle, buffer, 2, 100/portTICK_PERIOD_MS);
    if(ret != ESP_OK) {
        ESP_LOGE(GY_TAG, "write failed %x", ret);
    }

    reg = GY_21_READ_USER_REG;
    ret = i2c_master_transmit_receive(dev_handle, (uint8_t*)&reg, 1, buffer, 1, 100/portTICK_PERIOD_MS);
    if(ret != ESP_OK) {
        ESP_LOGE(GY_TAG, "read failed %x", ret);
    }

    if(config.data == buffer[0]) {
        ret = ESP_OK;
        uint8_t delaySetting = config.bits.RES_MSB | config.bits.RES_LSB;
        switch(delaySetting) {
            case 0:
                temperature_delay = GY_21_WAIT_TEMP_14_BIT;
                humidity_delay = GY_21_WAIT_HUMID_14_BIT;
                break;
            case 1:
                temperature_delay = GY_21_WAIT_TEMP_13_BIT;
                humidity_delay = GY_21_WAIT_HUMID_13_BIT;
                break;
            case 2:
                temperature_delay = GY_21_WAIT_TEMP_12_BIT;
                humidity_delay = GY_21_WAIT_HUMID_12_BIT;
                break;      
            case 3:
                temperature_delay = GY_21_WAIT_TEMP_11_BIT;
                humidity_delay = GY_21_WAIT_HUMID_11_BIT;
                break;
        }
    } else {
        ret = ESP_FAIL;
        temperature_delay = GY_21_WAIT_TEMP_14_BIT;
        humidity_delay = GY_21_WAIT_HUMID_14_BIT;
    }

    if (i2c_master_bus_rm_device(dev_handle) != ESP_OK) {
        ESP_LOGE(GY_TAG, "Remove Device failed");
    }

    return ret;
}

uint16_t gy21_read(int regToRead, int delay) {
    uint8_t buffer[10] = {0};
    uint8_t reg = regToRead;

    i2c_master_dev_handle_t dev_handle;
    if (i2c_master_bus_add_device(i2c_bus_handle, &gy21_dev_conf, &dev_handle) != ESP_OK) {
        ESP_LOGE(GY_TAG, "Device Bus add failed");
    }

    esp_err_t ret;
    // get the register over
    ret = i2c_master_transmit(dev_handle, (uint8_t*)&reg, 1, 100/portTICK_PERIOD_MS);
    if(ret != ESP_OK) {
        ESP_LOGE(GY_TAG, "write failed %x", ret);
    }

    vTaskDelay(delay / portTICK_PERIOD_MS); // wait till data is there
    
    ret = i2c_master_receive(dev_handle, buffer, 3, 100/portTICK_PERIOD_MS);
    if(ret != ESP_OK) {
        ESP_LOGE(GY_TAG, "read failed with code 0x%x", ret);
    }

    if (i2c_master_bus_rm_device(dev_handle) != ESP_OK) {
        ESP_LOGE(GY_TAG, "Remove Device failed");
    }

    // discard lower 2 bits
    uint16_t res = buffer[0] << 8 | (buffer[1] ^ 0x02);
    return res;
}

float gy21_readTemp() {
    uint16_t res = gy21_read(GY_21_TEMP_REG, temperature_delay);
    float temp = (0.002681274 * (float)res) - 46.85;
    return temp;
}

float gy21_readHumid() {
    uint16_t res = gy21_read(GY_21_HUMID_REG, humidity_delay);
    float temp = (0.001918334 * (float)res) - 6;

    // clip top and bottom
    if(temp < 0) {
        temp = 0;
    } else if(temp > 100) {
        temp = 100;
    }

    return temp;
}

float gy21_readCompensatedHumid() {
    float temperature = gy21_readTemp();
    float humid = gy21_readHumid();
    
    if(temperature > 0 && temperature < 80) {
        humid = humid + (25.0 - temperature) * GY_21_TEMP_COEFF;
    }

    // clip
    if(humid < 0) {
        humid = 0;
    } else if(humid > 100) {
        humid = 100;
    }

    return humid;
}

gy_meassurements_t gy21_readAll() {
    gy_meassurements_t meassurements;
    meassurements.temperature = gy21_readTemp();
    meassurements.humidity = gy21_readHumid();
    meassurements.compHumidity = gy21_readCompensatedHumid();
    return meassurements;
}