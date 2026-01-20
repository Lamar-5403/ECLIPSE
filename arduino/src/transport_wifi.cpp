#include "transport_wifi.h"
#include <Arduino.h>
#include "WiFi.h"
#include "config_wifi.h"
#include "frame_decoder.h"

WiFiClient client;
WiFiServer server(5230);

void transport_wifi_init() {
    Serial.begin(115200);

    WiFi.begin(SSID, PASS);

    Serial.println("Connecting to network...");

    // Wait for connection
    unsigned long startTime = millis();
    unsigned long lastCheck = 0;
    
    unsigned long now = millis();

    while (WiFi.status() != WL_CONNECTED) {

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