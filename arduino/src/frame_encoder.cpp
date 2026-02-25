#include "frame_encoder.h"
#include "transport_serial.h"
#include "transport_wifi.h"
#include "crc16_ccitt_false.h"

void calc_serialized_buf(const frame_t* f, uint8_t* out) {
    out[0] = f->start;
    out[1] = static_cast<int>(f->type); 
    out[2] = f->len;

    for (int i = 0; i < f->len; i++)
        out [3 + i] = f->payload[i];

    out[3 + f->len] = static_cast<uint8_t>(f->crc & 0xFF);
    out[3 + f->len + 1] = static_cast<uint8_t>((f->crc >> 8) & 0xFF);
}

void frame_encode(frame_t* f, msg_type_t type, const uint8_t* data, uint8_t len) {
    f->start = FRAME_START_BYTE;
    f->type = type;
    f->len = len;
    for (uint8_t i = 0; i < len; i++)
        f->payload[i] = data[i];
    f->crc = crc16_ccitt_false(reinterpret_cast<uint8_t*>(f), 3 + len);
}

void send_frame_serial(frame_t* f) {
    uint8_t total_len = 3 + f->len + 2;
    uint8_t buf[5 + FRAME_MAX_PAYLOAD];

    calc_serialized_buf(f, buf);

    for (int i = 0; i < total_len; i++)
        transport_serial_send_byte(buf[i]);
}

void send_frame_wifi(frame_t* f) {
    uint8_t total_len = 3 + f->len + 2;
    uint8_t buf[5 + FRAME_MAX_PAYLOAD];

    calc_serialized_buf(f, buf);

    for (int i = 0; i < total_len; i++)
        transport_wifi_send_byte(buf[i]);
}
