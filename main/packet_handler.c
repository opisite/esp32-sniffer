#include "packet_handler.h"
#include "uart_manager.h"
#include "utils.h"
#include "wifi_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAC_HDR_MIN_LENGTH 24
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

    if(is_beacon(&mac_hdr->frame_ctrl[0])) {
        beacon_handler(mac_hdr, length);
    }
        
    return;
}

/**
 * @brief Handles beacon frames received by packet_handler().
 * @param pkt A pointer to the start of the packet.
 * @param pkt_len The length of the packet.
 */
void beacon_handler(void *pkt, int pkt_len) {

    log_str("BEACON");

    wifi_beacon_hdr_t *beacon_hdr = (wifi_beacon_hdr_t *)pkt;
    uint8_t *end = (uint8_t *)pkt + pkt_len - FCS_LEN;
    
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
                log_str("SSID: %s", ssid_buf);
                break;
            }
            case 48: { // RSN
                uint16_t pairwise_cipher_suite_count = (param->value[7] << 8) | param->value[6];
                uint8_t *akm_suite_count_addr = &param->value[8] + (4 * pairwise_cipher_suite_count);
                uint16_t akm_suite_count = (akm_suite_count_addr[1] << 8) | akm_suite_count_addr[0];
                uint8_t *akm_suites = akm_suite_count_addr + 2;
                bool WPA2 = false;
                bool WPA3 = false;

                for(int x = 0; x < akm_suite_count; x++) {
                    uint8_t *suite =  &akm_suites[4 * x];
                    if(!(suite[0] == 0x00 && suite[1] == 0x0F && suite[2] == 0xAC))
                        continue;
                    
                    if(suite[3] == 0x02 || suite[3] == 0x04 || suite[3] == 0x08)
                        WPA2 = true;
                    if(suite[3] == 0x0C)
                        WPA3 = true;
                }

                log_str("Security: %s", WPA2 ? (WPA3 ? "WPA2 & WPA3" : "WPA2") : (WPA3 ? "WPA3" : "Unknown"));
            }
        }

        ptr = ptr + param->length + sizeof(wifi_tagged_param_t);
    }
    
    log_str("\n");
}
