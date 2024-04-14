#include <stdio.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifi_config.h"
#include "driver/uart.h"
#include "uart_manager.h"
#include "esp_log.h"


callback_entry_t callback_strs[] = {
    {'w', "Set wifi channel"},
};

callback_params_t *callback_params;

void input_callback(void) {
    switch(callback_params->code) {
        case 'w':
            set_wifi_channel(callback_params->arg);
            break;
    }

}

void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    callback_params = uart_manager_init(&callback_strs, (sizeof(callback_strs) / sizeof(callback_entry_t)), &input_callback);

    wifi_init_sniffer();

}
