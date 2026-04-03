#include <Arduino.h>
#include "control_authority_controller.h"
#include "transport_wifi.h"
#include "transport_serial.h"
#include "frame_decoder.h"
#include "types.h"

constexpr tactic_policy_t TACTIC_POLICY[] = {
    {0x43, true},
    {0x01, true},
    {0x06, true},
    {0x07, true},
    {0x08, false}
};

constexpr technique_policy_t TECHNIQUE_POLICY[] = {
    {0x01, true},
    {0x03, true},
    {0x04, true},
    {0x06, true}
};

static cooldown_entry_t COOLDOWN_TABLE[] = {
    {0x01, 5000, 0},
    {0x03, 30000, 0},
    {0x04, 60000, 0},
    {0x06, 10000, 0}
};

constexpr size_t TACTIC_POLICY_COUNT = sizeof(TACTIC_POLICY)/sizeof(tactic_policy_t);
constexpr size_t TECHNIQUE_POLICY_COUNT = sizeof(TECHNIQUE_POLICY)/sizeof(technique_policy_t);
constexpr size_t COOLDOWN_ENTRY_COUNT = sizeof(COOLDOWN_TABLE)/sizeof(cooldown_entry_t);

bool tactic_allowed(uint8_t tactic) {
    for (size_t i = 0; i < TACTIC_POLICY_COUNT; i++) {
        if (TACTIC_POLICY[i].tactic == tactic) {
            return TACTIC_POLICY[i].allowed;
        }
    }

    return false;
}

bool technique_allowed(uint8_t technique) {
    for (size_t i = 0; i < TECHNIQUE_POLICY_COUNT; i++) {
        if (TECHNIQUE_POLICY[i].technique == technique) {
            return TECHNIQUE_POLICY[i].allowed;
        }
    }

    return false;
}

bool cooldown_ready(uint8_t technique) {
    uint32_t now = millis();

    for (size_t i = 0; i < COOLDOWN_ENTRY_COUNT; i++) {
        if (COOLDOWN_TABLE[i].technique == technique) {
            if(now - COOLDOWN_TABLE[i].last_execution >= COOLDOWN_TABLE[i].cooldown_ms) {

                noInterrupts();
                COOLDOWN_TABLE[i].last_execution = now;
                interrupts();

                return true;
            }

            return false;
        }
    }

    return false;
}

void control_authority_controller_init() {
    // transport_wifi_register_status_cb(system_controller_wifi_status_cb);
    frame_decoder_register_handle_frame_cb(system_controller_handle_frame_cb);
}

void system_controller_handle_frame_cb(frame_t* rx_frame) {
    switch (rx_frame->type) {
        case msg_type_t::MSG_ARM:
            set_control_authority_state(control_authority_state_t::CAS_ARMING);
            
            if (rx_frame->length < 2) {
                set_control_authority_state(control_authority_state_t::CAS_DISARMED);
                return;
            }

            if (!tactic_allowed(rx_frame->payload[0])){
                set_control_authority_state(control_authority_state_t::CAS_DISARMED);
                return;
            }

            if (!technique_allowed(rx_frame->payload[1])){
                set_control_authority_state(control_authority_state_t::CAS_DISARMED);
                return;
            }

            if (!cooldown_ready(rx_frame->payload[1])){
                set_control_authority_state(control_authority_state_t::CAS_DISARMED);
                return;
            }

            set_control_authority_state(control_authority_state_t::CAS_ARMED);
            
            // rx_frame->payload[0] = {0x03};
            frame_encode(rx_frame, msg_type_t::MSG_AUTH_GRANTED, rx_frame->payload);
            send_frame_serial(rx_frame);
            break;

        case msg_type_t::MSG_DISARM:
            set_control_authority_state(control_authority_state_t::CAS_DISARMED);
            break;

        case msg_type_t::MSG_STATUS_REQUEST:
            // construct outgoing frame with the current control authority state
            break;

        case msg_type_t::MSG_HEARTBEAT:
            // reset local liveliness counter
            break;

        default:
            // invalid msg type
            // handled at verfication of frame in the decoder, state only reached here on system fault
            set_life_cycle_state(life_cycle_state_t::FAULT);
            break;
    }
}

// void system_controller_wifi_status_cb(connection_status_t status) {
//     if (status == connection_status_t::WIFI_DISCONNECTED) {
//         // either degrade system or reinitialize
//         // WiFi.disconnect();
//         // set_life_cycle_state(life_cycle_state_t::DEGRADED);
//         // transport_wifi_init();
//     } else if (status == connection_status_t::WIFI_FAILED) {
//         // reinitialize
//         // transport_wifi_init();
//     }
// }