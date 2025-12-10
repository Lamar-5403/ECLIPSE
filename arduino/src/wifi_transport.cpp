#include <Arduino.h>
#include "WiFi.h"

void wifi_transport_init() {
    char* SSID;
    char* PASS;

    WiFi.begin(SSID, PASS);
}