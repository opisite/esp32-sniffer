#include "wifi_config.h"
#include "packet_handler.h"
#include "uart_manager.h"

/**
 * @brief Initializes the Wi-Fi in promiscuous mode.
 */
void wifi_init_sniffer(void) {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_NULL));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous(true));
    ESP_ERROR_CHECK(esp_wifi_set_promiscuous_rx_cb(packet_handler));

    set_wifi_channel(6);
}

void set_wifi_channel(uint8_t channel) {
    log_str("Setting WIFI Channel to Channel %d", channel);
    esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
}
