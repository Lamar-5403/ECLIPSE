#include "control_authority_controller.h"
#include "transport_wifi.h"
#include "frame_decoder.h"
#include "types.h"

void control_authority_controller_init() {
    transport_wifi_register_status_cb(system_controller_wifi_status_cb);
    frame_decoder_register_handle_frame_cb(system_controller_handle_frame_cb);
}

void system_controller_handle_frame_cb(frame_t* rx_frame) {
    switch (rx_frame->type) {
        case msg_type_t::MSG_ARM:
            set_control_authority_state(control_authority_state_t::CAS_ARMING);
            // check cooldowns, verify scope, etc
            set_control_authority_state(control_authority_state_t::CAS_ARMED);
            // send authorization frame
            break;

        case msg_type_t::MSG_DISARM:
            set_control_authority_state(control_authority_state_t::CAS_DISARMED);
            break;

        case msg_type_t::MSG_STATUS_REQUEST:
            // construct outgoing frame with the current control authority state
            break;

        case msg_type_t::MSG_HEARTBEAT:
            // construct outgoing frame with verification of live connection
            break;

        default:
            // invalid msg type
            // handled at verfication of frame in the decoder, state only reached here on system fault
            set_life_cycle_state(life_cycle_state_t::FAULT);
            break;
    }
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