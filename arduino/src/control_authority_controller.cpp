#include "control_authority_controller.h"
#include "transport_wifi.h"
#include "frame_decoder.h"

void control_authority_controller_init() {
    transport_wifi_register_status_cb(system_controller_wifi_status_cb);
    frame_decoder_register_handle_frame_cb(system_controller_handle_frame_cb);
}

void system_controller_handle_frame_cb(frame_t* rx_frame) {
    // do something
}

void system_controller_wifi_status_cb(connection_status_t status) {
    if (status == connection_status_t::WIFI_DISCONNECTED) {
        // either degrade system or reinitialize
        // WiFi.disconnect();
        // set_life_cycle_state(life_cycle_state_t::DEGRADED);
        // transport_wifi_init();
    } else if (status == connection_status_t::WIFI_FAILED) {
        // reinitialize
        // transport_wifi_init();
    }
}