#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include "esp_wifi_types.h"

typedef struct {
    uint8_t frame_ctrl[2];
    uint8_t duration_id[2];
    uint8_t addr1[6];
    uint8_t addr2[6];
    uint8_t addr3[6];
    uint8_t seq_ctrl[2];
} wifi_mac_hdr_t;

void packet_handler(void* buff, wifi_promiscuous_pkt_type_t type);

#endif // PACKET_HANDLER_H