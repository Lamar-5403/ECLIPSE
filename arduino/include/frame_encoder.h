#pragma once
#include <cstddef>
#include <cstdint>
#include "frame.h"

uint16_t crc16_ccitt_false(const uint8_t *, size_t);
void encode_frame(frame_t* f, msg_type_t, const uint8_t*, uint8_t);