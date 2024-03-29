#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include "esp_wifi.h"

void wifi_init_sniffer(void);
void set_wifi_channel(uint8_t channel);

#endif // WIFI_CONFIG_H
