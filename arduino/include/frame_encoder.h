#pragma once
#include <cstdint>
#include "types.h"
#include "transport_serial.h"
#include "transport_wifi.h"
#include "crc16_ccitt_false.h"

void encode_frame(frame_t* f, msg_type_t, const uint8_t*, uint8_t);