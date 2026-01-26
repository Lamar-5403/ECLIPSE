#include "frame_decoder.h"
#include "frame.h"
#include "system_controller.h"

static frame_decoder_state_t decoder_state = frame_decoder_state_t::WAIT_START;
static uint8_t payload_index = 0;
static uint16_t crc_calc = 0;
static frame_t rx_frame;

void frame_decoder_reset() {
    decoder_state = frame_decoder_state_t::WAIT_START;
    payload_index = 0;
    crc_calc = 0;       // crc init vlaue
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
            static uint8_t crc_byte_index = 0;
            ((uint8_t*) &rx_frame.crc)[crc_byte_index++] = b;
            if (crc_byte_index == 2) {
                crc_byte_index = 0;
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