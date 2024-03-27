#include "utils.h"
#include "uart_manager.h"
#include <stdio.h>

#define MAC_STR_SIZE 18
#define IP_STR_SIZE  17

/**
 * @brief Converts a MAC address to a human-readable string.
 * @param mac The MAC address.
 */
char* mac_address_to_string(uint8_t* mac) {
    char *str = (char *)malloc(MAC_STR_SIZE);
    snprintf(str, MAC_STR_SIZE, "%02x:%02x:%02x:%02x:%02x:%02x",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return str;
}

/**
 * @brief Converts an IP address to a human-readable string.
 * @param ip The IPv4 address.
 */
char* ipv4_address_to_string(uint8_t* ip) {
    char *str = (char *)malloc(IP_STR_SIZE);
    snprintf(str, IP_STR_SIZE, "%d:%d:%d:%d",
            ip[0], ip[1], ip[2], ip[3]);
    return str;
}

bool is_broadcast(uint8_t *mac) {
    for(int x = 0; x < 6; x++) {
        if(mac[x] != 0xFF)
            return false;
    }
    return true;
}

bool is_beacon(uint8_t *fc) {
    if((*fc & 0xFC) == 0x80) {
        return true;
    }
    return false;
}

void print_byte(void *byte) {
    uint8_t *hex = (uint8_t *)byte;
    log_str("%s(): %X", __FUNCTION__, *hex);
}

void print_raw_payload(void *buf, int len) {
    uint8_t *byte = buf;

    for(int x = 0; x < len; x++) {
        log_str("%02X", *byte);
        byte++;
    }
    log_str("--------------------------");
}
