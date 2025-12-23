#include "frame.h"
#include <cstddef>

uint16_t crc16_ccitt_false(const uint8_t *data, size_t len) {
    
    uint16_t crc = 0xFFFF;

    for (uint16_t i = 0; i < len; i++) {
        crc ^= (uint16_t)data[i] << 8;

        for ( uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

void encode_frame(frame_t* f, msg_type_t type, const uint8_t* data, uint8_t len) {
    f->start = FRAME_START_BYTE;
    f->type = type;
    f->len = len;
    for (uint8_t i = 0; i < len; i++)
        f->payload[i] = data[i];
    f->crc = crc16_ccitt_false((uint8_t*)f, 3 + len);
}