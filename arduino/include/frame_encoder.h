#pragma once
#include <cstddef>
#include <cstdint>
#include "types.h"

void calc_serialized_buf(const frame_t*, uint8_t*);
void frame_encode(frame_t*, msg_type_t, const uint8_t*);
void send_frame_serial(frame_t*);
void send_frame_wifi(frame_t*);