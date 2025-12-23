#include "transport_wifi.h"
#include <Arduino.h>
#include "WiFi.h"
#include "config_wifi.h"
#include "frame_decoder.h"

void transport_wifi_init() {
    WiFi.begin(SSID, PASS);

    // Wait for connection
    unsigned long startTime = millis();
    unsigned long lastCheck = 0;

    while (WiFi.status() != WL_CONNECTED) {

        unsigned long now = millis();

        if (now - startTime >= 10000) {
            Serial.println("Could not connect to network.");
            exit(1);
        } else if (now - lastCheck >= 250) {
            lastCheck = now;
            Serial.println(WiFi.status());
        }
    }

    Serial.println("Connected.");
}

void transport_wifi_poll() {
    
}

void transport_wifi_send_byte(const uint8_t*, size_t) {
    
}