#include "transport_wifi.h"
#include <Arduino.h>
#include "WiFi.h"
#include "config_wifi.h"
#include "frame_decoder.h"

WiFiClient client;
connection_status_t connection_status = connection_status_t::WIFI_UNINITIALIZED;

long connection_attempt_time = 0;

void transport_wifi_init() {
    connection_status_t connection_status = connection_status_t::WIFI_CONNECTING;

    Serial.begin(115200);

    WiFi.begin(SSID, PASS);
    client.connect(IP, PORT);

    Serial.println("Connecting to network...");

    // Record timestamp for timeout calculation
    connection_attempt_time = millis();
}

void transport_wifi_poll() {

    // Switch on connection_status
    switch (connection_status) {
    
        case connection_status_t::WIFI_CONNECTING:
            if (WiFi.status() == WL_CONNECTED && client.connected()) {
                connection_status = connection_status_t::WIFI_CONNECTED;
            } else if (millis() - connection_attempt_time >= 10000) {
                WiFi.disconnect();
                client.stop();
                connection_status = connection_status_t::WIFI_FAILED;
                Serial.print("Network connection attempt timed out.");
                // Report failure to system controller
                return;
            } else {
                // connection not yet established. return and wait for connection
                return;
            }
            break;
    
        case connection_status_t::WIFI_CONNECTED:
            if (WiFi.status() != WL_CONNECTED || !client.connected()) {
                connection_status = connection_status_t::WIFI_DISCONNECTED;
                WiFi.disconnect();
                client.stop();
                // Report dropped connection to system controller
                return;
            } else {
                // Drain available bytes to frame decoder
                while (client.available() > 0) {
                    frame_decoder_process_byte(client.read());
                }
                return;
            }
            // check if still connected, if not report dropped connection and return, if so drain bytes and return
            break;

        default:
            // system either uninitialized or has not been or is no longer connected, requiring system controller intervention
            break;
    }
}

void transport_wifi_send_byte(const uint8_t* byte, size_t size) {
    client.write(byte, size);
}