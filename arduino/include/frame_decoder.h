#pragma once
#include "frame.h"

// Enum for finite state machine for decoder 
enum class frame_decoder_state_t {
    WAIT_START,
    READ_TYPE,
    READ_LEN,
    READ_PAYLOAD,
    READ_CRC
};

void frame_decoder_reset();
void frame_decoder_process_byte(uint8_t);