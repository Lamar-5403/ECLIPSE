#pragma once
#include <cstdint>

typedef void (*process_byte_cb_t)(uint8_t);
typedef void (*frame_decoder_reset_cb_t)();

void transport_serial_register_process_byte_cb(process_byte_cb_t cb);
void transport_serial_register_decoder_reset_cb(frame_decoder_reset_cb_t cb);

void transport_serial_init();
void transport_serial_poll();
void transport_serial_send_byte(const uint8_t);