#pragma once
#include <cstddef>
#include <cstdint>
#include <Arduino.h>
#include "WiFi.h"
#include "config_wifi.h"
#include "frame_decoder.h"
#include "control_authority_controller.h"

enum class connection_status_t {
    WIFI_UNINITIALIZED,
    WIFI_CONNECTING,
    WIFI_CONNECTED,
    WIFI_DISCONNECTED,
    WIFI_FAILED
};

void transport_wifi_init();
void transport_wifi_poll();
void transport_wifi_send_byte(const uint8_t*, size_t);