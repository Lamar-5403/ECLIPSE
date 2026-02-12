#pragma once
#include <cstdint>
#include "types.h"

void encode_frame(frame_t*, msg_type_t, const uint8_t*, uint8_t);
void send_frame_serial(frame_t*);
void send_frame_wifi(frame_t*);