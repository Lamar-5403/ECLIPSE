#include "transport_wifi.h"
#include <Arduino.h>
#include "WiFi.h"
#include "config_wifi.h"
#include "frame_decoder.h"

WiFiClient client;
connection_status_t connection_status = WIFI_UNITIALIZED;

long connection_attempt_start_time = 0;

void transport_wifi_init() {
    connection_status_t connection_status = WIFI_CONNECTING;

    Serial.begin(115200);

    WiFi.begin(SSID, PASS);

    Serial.println("Connecting to network...");

    // Record timestamp for timeout calculation
    connection_attempt_start_time = millis();
}

void transport_wifi_poll() {

    // Switch on connection_status
    switch (connection_status) {
    
        case WIFI_CONNECTING:
            // if connected drain bytes, if not: have we timed out, if not return and wait for connection
        break;
    
        case WIFI_CONNECTED:
            // check if still connected, if not report dropped connection and return, if so drain bytes and return
        break;

        default:
            // system either uninitialized or has not been or is no longer connected, requiring system controller intervention
            break;
    }








    
    // On successful connection
    if (connection_status = WIFI_CONNECTING) {
        if (WiFi.status() == WL_CONNECTED) {
            connection_status == WIFI_CONNECTED;
        }
    }
    
    // Ensure client maintains active connection
    if (connection_status == WIFI_CONNECTED) {
        if (WiFi.status() != WL_CONNECTED) {
            connection_status = WIFI_DISCONNECTED;
            // Report dropped connection to system controller
        } else {
            // Drain available bytes to frame decoder
            while (client.available() > 0) {
                frame_decoder_process_byte(client.read());
            }
            client.flush();
            return;
        }
    }
    
    // Check for connection timeout
    if (millis() - connection_attempt_start_time >= 10000) {
        WiFi.disconnect();
        connection_status = WIFI_FAILED;
        // Report failure to system controller
        Serial.print("Network connection attempt timed out.")
    }    
}

void transport_wifi_send_byte(const uint8_t*, size_t) {
    
}