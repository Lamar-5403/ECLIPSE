#pragma once
#include <cstdint>
#include <Arduino.h>
#include "Wifi.h"
#include "config_wifi.h"
#include "types.h"

typedef void(*wifi_status_cb_t)(connection_status_t);
typedef void(*process_byte_cb_t)(uint8_t);
typedef void(*frame_decoder_reset_cb_t)();

void transport_wifi_register_status_cb(wifi_status_cb_t cb);
void transport_wifi_register_process_byte_cb(process_byte_cb_t cb);
void transport_wifi_register_decoder_reset_cb(frame_decoder_reset_cb_t cb);

void transport_wifi_init();
void transport_wifi_poll();
void transport_wifi_send_byte(const uint8_t);
