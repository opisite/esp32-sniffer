#include "packet_handler.h"
#include "uart_manager.h"
#include "utils.h"
#include "wifi_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAC_HDR_MIN_LENGTH 24
#define QOS_HEADER_LENGTH 2


#define TEST_MAC "01:23:45:67:89:01"
#define FCS_LEN 4

/**
 * @brief Handles incoming packets in promiscuous mode.
 * @param buf The packet buffer.
 * @param type The type of packet.
 */
void packet_handler(void *buf, wifi_promiscuous_pkt_type_t type) {
    if (type != WIFI_PKT_MGMT) {
        return;
    }

    wifi_promiscuous_pkt_t *pkt = (wifi_promiscuous_pkt_t *)buf;
    int length = pkt->rx_ctrl.sig_len;
    wifi_mac_hdr_t *mac_hdr = (wifi_mac_hdr_t *)pkt->payload;



    if(is_beacon(mac_hdr->addr1)) {
        beacon_handler(mac_hdr, length);
    }
        
    
    return;

}

void beacon_handler(void *hdr, int buf_len) {

    log_str("BEACON");

    wifi_beacon_hdr_t *beacon_hdr = (wifi_beacon_hdr_t *)hdr;
    uint8_t *end = (uint8_t *)hdr + buf_len - FCS_LEN;
    
    char *MAC = mac_address_to_string(beacon_hdr->addr3);
    log_str("MAC: %s", MAC);
    free(MAC);

    uint8_t *ptr = (uint8_t *)&beacon_hdr->tagged_params;
    while(ptr + 2 < end) {
        wifi_tagged_param_t *param = (wifi_tagged_param_t *)ptr;
        switch(param->element_id) {
            case 0: { // SSID
                uint8_t ssid_length = param->length;
                uint8_t ssid_buf[ssid_length + 1];
                memcpy(ssid_buf, param->value, ssid_length);
                ssid_buf[ssid_length] = '\0';
                log_str("SSID: %s\n", ssid_buf);
                break;
            }
        }

        ptr = ptr + param->length + sizeof(wifi_tagged_param_t);
    }
    
}