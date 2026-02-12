#include "frame_encoder.h"
#include "transport_serial.h"
#include "transport_wifi.h"
#include "crc16_ccitt_false.h"

void encode_frame(frame_t* f, msg_type_t type, const uint8_t* data, uint8_t len) {
    f->start = FRAME_START_BYTE;
    f->type = static_cast<uint8_t>(type);
    f->len = len;
    for (uint8_t i = 0; i < len; i++)
        f->payload[i] = data[i];
    f->crc = crc16_ccitt_false(reinterpret_cast<uint8_t*>(f), 3 + len);
}

void send_frame_serial(frame_t* f) {
    // first three bytes of frame f, len bytes of payload, final two bytes
    //transport_serial_send_byte();
}

void send_frame_wifi(frame_t* f) {
    // first three bytes of frame f, len bytes of payload, final two bytes
    //transport_wifi_send_byte();
}