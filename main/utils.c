#include "utils.h"
#include <stdio.h>

/**
 * @brief Converts a MAC address to a human-readable string.
 * @param mac The MAC address.
 * @param buffer The buffer to store the string representation.
 * @param buffer_len The length of the buffer.
 * @return A pointer to the buffer.
 */
char* mac_address_to_string(uint8_t* mac, char* buffer, int buffer_len) {
    snprintf(buffer, buffer_len, "%02x:%02x:%02x:%02x:%02x:%02x",
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return buffer;
}
