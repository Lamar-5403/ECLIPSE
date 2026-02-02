#include "frame_encoder.h"

void encode_frame(frame_t* f, msg_type_t type, const uint8_t* data, uint8_t len) {
    f->start = FRAME_START_BYTE;
    f->type = static_cast<uint8_t>(type);
    f->len = len;
    for (uint8_t i = 0; i < len; i++)
        f->payload[i] = data[i];
    f->crc = crc16_ccitt_false(reinterpret_cast<uint8_t*>(f), 3 + len);
}