#pragma once
#include "control_authority_controller.h"
#include "crc16_ccitt_false.h"
#include "types.h"

void frame_decoder_reset();
void frame_decoder_process_byte(uint8_t);