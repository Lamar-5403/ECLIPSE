#pragma once
#include <cstdint>
#include "types.h"

typedef void (*handle_frame_cb_t)(frame_t*);

void frame_decoder_register_handle_frame_cb(handle_frame_cb_t);

void frame_decoder_init();
void frame_decoder_reset();
void frame_decoder_process_byte_cb(uint8_t);