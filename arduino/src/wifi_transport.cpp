#include <Arduino.h>
#include "WiFi.h"
#include "wifi_config.h"

void wifi_transport_init() {
    WiFi.begin(SSID, PASS);
}

void wifi_poll() {
    // do something;
}