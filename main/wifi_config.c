#include "wifi_config.h"

/**
 * @brief Initializes the Wi-Fi in promiscuous mode.
 */
void wifi_init_sniffer(void) {
    // Initialize NVS
    // Initialize TCP/IP stack
    // Initialize Wi-Fi with `esp_wifi_init`
    // Set Wi-Fi in promiscuous mode with `esp_wifi_set_promiscuous`
    // Set the promiscuous filter to only listen to specific packet types if necessary
    // Start Wi-Fi with `esp_wifi_start`
    // Register the packet handler callback with `esp_wifi_set_promiscuous_rx_cb`

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_NULL));
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous(true));


}