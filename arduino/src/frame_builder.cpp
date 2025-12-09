#include "frame.h"

void frame_build(frame_t* f, msg_type_t type, const uint8_t* data, uint8_t len) {
    f->start = FRAME_START_BYTE;
    f->type = type;
    f->len = len;
    for (uint8_t i = 0; i < len; i++)
        f->payload[i] = data[i];
    f->crc = crc16((uint8_t*)f, 3 + len);       // crc16 file still needs to be implemented
}