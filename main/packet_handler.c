#include "packet_handler.h"
#include <stdio.h>

/**
 * @brief Handles incoming packets in promiscuous mode.
 * @param buff The packet buffer.
 * @param type The type of packet.
 */
void packet_handler(void* buff, wifi_promiscuous_pkt_type_t type) {
    // Check the packet type
    // Parse the packet (e.g., extract MAC addresses, packet size)
    // Print or log the packet information
}
