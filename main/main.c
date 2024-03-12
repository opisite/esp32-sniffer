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


void app_main(void) {
    // Initialize NVS
    // Call `wifi_init_sniffer` to set up Wi-Fi in promiscuous mode
    // Other setup or loop code as 

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    uart_manager_init();

    wifi_init_sniffer();

}
