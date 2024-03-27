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
    uint8_t next[0];
} __attribute__((packed)) wifi_mac_hdr_t;

typedef struct {
    uint8_t frame_ctrl[2];
    uint8_t duration_id[2];
    uint8_t addr1[6];
    uint8_t addr2[6];
    uint8_t addr3[6];
    uint8_t seq_ctrl[2];
    uint8_t timestamp[8];
    uint8_t beacon_interval[2];
    uint8_t capabilities_info[2];
    uint8_t tagged_params[0];
} __attribute__((packed)) wifi_beacon_hdr_t;

typedef struct {
    uint8_t element_id;
    uint8_t length;
    uint8_t value[0];
} __attribute__((packed)) wifi_tagged_param_t;

typedef struct {
    uint8_t DSAP;
    uint8_t SSAP;
    uint8_t ctrl;
    uint8_t OUI[3];
    uint8_t PID[2];
    uint8_t payload[0];
} __attribute__((packed)) llc_snap_hdr_t;

typedef struct {
    uint8_t destination_mac[6];
    uint8_t source_mac[6];
    uint8_t ethertype[2];
    uint8_t payload[0];
} __attribute__((packed)) ethernet2_hdr_t;

typedef struct {
    uint8_t version_ihl;
    uint8_t type_of_service;
    uint8_t total_length[2];
    uint8_t identification[2];
    uint8_t flags_fragment_offset[2];
    uint8_t time_to_live;
    uint8_t protocol;
    uint8_t header_checksum[2];
    uint8_t source_address[4];
    uint8_t destination_address[4];
    uint8_t payload[0];
} __attribute__((packed)) ipv4_hdr_t;


void packet_handler(void *buf, wifi_promiscuous_pkt_type_t type);
void llc_snap_handler(void *hdr);
void ethernet2_handler(void *hdr);
void beacon_handler(void *hdr, int buf_len);

#endif // PACKET_HANDLER_H