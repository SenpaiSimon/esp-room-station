#pragma once

#include "gy_21/gy_21.h"
#include "webserver/creds.h"
#include "config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include <esp_http_server.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <netdb.h>
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "cJSON.h"

void wifiConnect();
httpd_handle_t start_webserver(void);
