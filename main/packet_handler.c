#include "packet_handler.h"
#include "uart_manager.h"
#include "utils.h"
#include "wifi_config.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Handles incoming packets in promiscuous mode.
 * @param buff The packet buffer.
 * @param type The type of packet.
 */
void packet_handler(void* buf, wifi_promiscuous_pkt_type_t type) {
    if (type != WIFI_PKT_MGMT && type != WIFI_PKT_DATA) {
        return;
    }

    wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
    uint16_t payload_length = pkt->rx_ctrl.sig_len;
    wifi_mac_hdr_t *hdr = (wifi_mac_hdr_t *)pkt->payload;

    if(is_broadcast(&hdr->addr1)) {
        return;
    }

    char buffer[128];
    char mac[18];

    mac_address_to_string(&hdr->addr1, mac, sizeof(mac));
    snprintf(buffer, sizeof(buffer), "Destination addr: %s", mac);
    uart_print(buffer);
    
    mac_address_to_string(&hdr->addr2, mac, sizeof(mac));
    snprintf(buffer, sizeof(buffer), "Source addr: %s", mac);
    uart_print(buffer);
    
    uart_print("\r\n");
}
