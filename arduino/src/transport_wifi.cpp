#include "transport_wifi.h"

WiFiClient client;
connection_status_t connection_status = connection_status_t::WIFI_UNINITIALIZED;
constexpr unsigned long wifi_connection_timeout_ms = 10'000;
long connection_attempt_time = 0;

void transport_wifi_init() {
    frame_decoder_reset();
    connection_status_t connection_status = connection_status_t::WIFI_CONNECTING;

    WiFi.begin(SSID, PASS);
    client.connect(IP, PORT);

    // Record timestamp for timeout calculation
    connection_attempt_time = millis();
}

void transport_wifi_poll() {

    // Switch on connection_status
    switch (connection_status) {
    
        case connection_status_t::WIFI_CONNECTING:
            if (WiFi.status() == WL_CONNECTED && client.connected()) {
                connection_status = connection_status_t::WIFI_CONNECTED;
            } else if (millis() - connection_attempt_time >= wifi_connection_timeout_ms) {
                connection_status = connection_status_t::WIFI_FAILED;
                report_status(connection_status);
                return;
            } else {
                // connection not yet established. return and wait for connection
                return;
            }
            break;
    
        case connection_status_t::WIFI_CONNECTED:
            if (WiFi.status() != WL_CONNECTED || !client.connected()) {
                connection_status = connection_status_t::WIFI_DISCONNECTED;
                // Report dropped connection to system controller
                report_status(connection_status);
                return;
            } else {
                // Drain available bytes to frame decoder
                while (client.available() > 0) {
                    frame_decoder_process_byte(client.read());
                }
                return;
            }
            break;

        default:
            // system either uninitialized or has not been or is no longer connected, requiring system controller intervention
            break;
    }
}

void transport_wifi_send_byte(const uint8_t* byte, size_t size) {
    client.write(byte, size);
}