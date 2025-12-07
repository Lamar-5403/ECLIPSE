#include "frame.h"

static frame_parse_state_t state = WAIT_START;
static uint8_t payload_index = 0;
static uint16_t crc_calc = 0;

void frame_reset() {
    state = WAIT_START;
    payload_index = 0;
    crc_calc = 0;       // crc init vlaue
}

bool frame_process_byte(frame_t* f, uint8_t b) {
    switch (state) {
        case WAIT_START:
            if (b == FRAME_START_BYTE) {
                f->start = b;
                payload_index = 0;
                crc_calc = 0;
                state = READ_TYPE;
            }
            return false;
        
        case READ_TYPE:
            f->type = b;
            state = READ_LEN;
            return false;

        case READ_LEN:
            f->len = b;
            payload_index = 0;
            state = (b == 0 ? READ_CRC : READ_PAYLOAD);     // if payload length is 0, skip to crc check, else read payload 
            return false;

        case READ_PAYLOAD:
            f->payload[payload_index++] = b;
            if (payload_index == f->len)
                state = READ_CRC;
            return false;

        case READ_CRC:
            static uint8_t crc_byte_index = 0;
            ((uint8_t*)&f->crc)[crc_byte_index++] = b;
            if (crc_byte_index == 2) {
                crc_byte_index = 0;
                bool verified = (f->crc == crc_calc);
                frame_reset();
                return verified;
            }
            return false;
    }
    return false;
}

void handle_frame(frame_t* f) {
    
}