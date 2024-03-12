#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>

void mac_address_to_string(uint8_t* mac, char* buffer, int buffer_len);
bool is_broadcast(uint8_t* mac);

#endif // UTILS_H
