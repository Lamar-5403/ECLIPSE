#include "control_authority_controller.h"
#include "transport_wifi.h"
#include "transport_serial.h"
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

            // TEST PURPOSES ONLY
            if (rx_frame->payload[0] == 0xAC && rx_frame->payload[1] == 0xDC) {

                // Print received frame
                Serial.print("Frame Received: type: ");
                Serial.print((int)rx_frame->type);
                Serial.print(", payload: 0x");
                for (int i = 0; i < rx_frame->len; i++) {
                    Serial.print("0x");
                    Serial.print(rx_frame->payload[i]);
                    Serial.print(", ");
                }
                Serial.print("crc: ");
                Serial.print(rx_frame->crc);
                
                // Generate outgoing frame
                uint8_t test_payload[] = {0x56, 0x78};
                frame_encode(rx_frame, msg_type_t::MSG_STATUS_RESPONSE, test_payload, sizeof(test_payload));
                
                // Print outgoing frame
                Serial.print("Frame generated: type: ");
                Serial.print((int)rx_frame->type);
                Serial.print(", payload: 0x");
                for (int i = 0; i < rx_frame->len; i++) {
                    Serial.print("0x");
                    Serial.print(rx_frame->payload[i]);
                    Serial.print(", ");
                }
                Serial.print("crc: ");
                Serial.print(rx_frame->crc);
                
                // Send frame
                send_frame_serial(rx_frame);
            }
            // TEST PURPOSES ONLY

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