#include "control_authority_controller.h"

void system_controller_handle_frame(frame_t* rx_frame) {
    // do something
}

void report_status(connection_status_t status) {
    if (status == connection_status_t::WIFI_DISCONNECTED) {
        // either degrade system or reinitialize
        // set_life_cycle_state(life_cycle_state_t::DEGRADED);
        // transport_wifi_init();
    } else if (status == connection_status_t::WIFI_FAILED) {
        // reinitialize
        // transport_wifi_init();
    }
}