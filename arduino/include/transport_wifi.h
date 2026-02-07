#pragma once
#include <cstdint>
#include <Arduino.h>
#include "WiFi.h"
#include "config_wifi.h"
#include "types.h"

void transport_wifi_init();
void transport_wifi_poll();
void transport_wifi_send_byte(const uint8_t*, size_t);