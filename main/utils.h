#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>
#include "time.h"

char* mac_address_to_string(uint8_t *mac);
char* ipv4_address_to_string(uint8_t *ip);
bool is_broadcast(uint8_t *mac);
bool is_beacon(uint8_t *fc);
void print_byte(void *byte);
void print_raw_payload(void *buf, int len);

#endif // UTILS_H
