#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include "esp_wifi_types.h"

void packet_handler(void* buff, wifi_promiscuous_pkt_type_t type);

#endif // PACKET_HANDLER_H