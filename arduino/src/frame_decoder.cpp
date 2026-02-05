#include "frame_decoder.h"

static frame_decoder_state_t decoder_state = frame_decoder_state_t::WAIT_START;
static uint8_t payload_index = 0;
static uint16_t crc_calc = 0;
static frame_t rx_frame;
static uint8_t crc_byte_idx = 0;

void frame_decoder_reset() {
    decoder_state = frame_decoder_state_t::WAIT_START;
    payload_index = 0;
    crc_calc = 0;       // crc init vlaue
    crc_byte_idx = 0;
}

void frame_decoder_process_byte(uint8_t b) {
    switch (decoder_state) {
        case frame_decoder_state_t::WAIT_START:
            if (b == FRAME_START_BYTE) {
                rx_frame.start = b;
                payload_index = 0;
                crc_calc = 0;
                decoder_state = frame_decoder_state_t::READ_TYPE;
            }
            break;
        
        case frame_decoder_state_t::READ_TYPE:
            rx_frame.type = b;
            decoder_state = frame_decoder_state_t::READ_LEN;
            break;

        case frame_decoder_state_t::READ_LEN:
            rx_frame.len = b;
            payload_index = 0;
            decoder_state = (b == 0 ? frame_decoder_state_t::READ_CRC : frame_decoder_state_t::READ_PAYLOAD);     // if payload length is 0, skip to crc check, else read payload 
            break;

        case frame_decoder_state_t::READ_PAYLOAD:
            rx_frame.payload[payload_index++] = b;
            if (payload_index == rx_frame.len)
                decoder_state = frame_decoder_state_t::READ_CRC;
            break;

        case frame_decoder_state_t::READ_CRC:

            if (crc_byte_idx == 0) {
                rx_frame.crc = b << 8;  // Store MSB 
            } else {
                rx_frame.crc |= b;  // LSB
            }
            crc_byte_idx++;

            if (crc_byte_idx == 2) {
                crc_byte_idx = 0;
                crc_calc = crc16_ccitt_false(reinterpret_cast<const uint8_t*>(&rx_frame), (3 + rx_frame.len));
                bool verified = (rx_frame.crc == crc_calc);
                if (verified) {
                    system_controller_handle_frame(&rx_frame);
                }

                frame_decoder_reset();
            }
            break;

        default:
            // invalid state reached
            break;
    }
}