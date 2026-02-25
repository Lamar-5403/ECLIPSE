#include "transport_wifi.h"

WiFiClient client;
connection_status_t connection_status = connection_status_t::WIFI_UNINITIALIZED;
constexpr unsigned long wifi_connection_timeout_ms = 10'000;
unsigned long connection_attempt_time = 0;

static wifi_status_cb_t status_cb = nullptr;
static process_byte_cb_t process_byte_cb = nullptr;
static frame_decoder_reset_cb_t frame_decoder_reset_cb = nullptr;

void transport_wifi_register_status_cb(wifi_status_cb_t cb) {
    status_cb = cb;
}

void transport_wifi_register_process_byte_cb(process_byte_cb_t cb) {
    process_byte_cb = cb;
}

void transport_wifi_register_decoder_reset_cb(frame_decoder_reset_cb_t cb) {
    frame_decoder_reset_cb = cb;
}

void transport_wifi_init() {
    connection_status = connection_status_t::WIFI_CONNECTING;

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
                // callback hook
                if (status_cb) {
                    status_cb(connection_status);
                }
                return;
            } else {
                // connection not yet established. return and wait for connection
                return;
            }
    
        case connection_status_t::WIFI_CONNECTED:
            if (WiFi.status() != WL_CONNECTED || !client.connected()) {
                connection_status = connection_status_t::WIFI_DISCONNECTED;
                // Report dropped connection to system controller
                // callback hook
                if (status_cb) {
                    status_cb(connection_status);
                }
                return;
            } else {
                // Drain available bytes to frame decoder
                if (frame_decoder_reset_cb) {
                    frame_decoder_reset_cb();
                }
                while (client.available() > 0) {
                    //callback hook
                    if (process_byte_cb) {
                        process_byte_cb(client.read());
                    }
                }
                return;
            }

        default:
            // system either uninitialized or has not been or is no longer connected, requiring system controller intervention
            break;
    }
}

void transport_wifi_send_byte(const uint8_t byte) {
    client.write(byte);
}