#pragma once
#include <cstddef>
#include <cstdint>

typedef void (*process_byte_cb_t)(uint8_t);
void transport_serial_register_process_byte_cb(process_byte_cb_t cb);

void transport_serial_init();
void transport_serial_poll();
void transport_serial_send_byte(const uint8_t*, size_t);