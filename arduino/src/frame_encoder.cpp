#if !defined(frame_layer_unit_test)
#include "transport_serial.h"
#include "transport_wifi.h"
#endif

#include "frame_encoder.h"
#include "crc16_ccitt_false.h"

void calc_serialized_buf(const frame_t* f, uint8_t* out) {
    out[0] = f->start;
    out[1] = static_cast<int>(f->type); 
    out[2] = f->length;

    for (int i = 0; i < f->length; i++)
        out [3 + i] = f->payload[i];

    out[3 + f->length] = static_cast<uint8_t>((f->crc >> 8) & 0xFF);   // MSB
    out[3 + f->length + 1] = static_cast<uint8_t>(f->crc & 0xFF);      // LSB
}

void frame_encode(frame_t* f, msg_type_t type, const uint8_t* data) {
    f->start = FRAME_START_BYTE;
    f->type = type;
    f->length = sizeof(data);
    for (uint8_t i = 0; i < f->length; i++)
        f->payload[i] = data[i];
    f->crc = crc16_ccitt_false(reinterpret_cast<uint8_t*>(f), 3 + f->length);
}

#if !defined(frame_layer_unit_test)
void send_frame_serial(frame_t* f) {
    uint8_t total_len = 3 + f->length + 2;
    uint8_t buf[5 + FRAME_MAX_PAYLOAD];

    calc_serialized_buf(f, buf);

    for (int i = 0; i < total_len; i++)
        transport_serial_send_byte(buf[i]);
}

void send_frame_wifi(frame_t* f) {
    uint8_t total_len = 3 + f->length + 2;
    uint8_t buf[5 + FRAME_MAX_PAYLOAD];

    calc_serialized_buf(f, buf);

    for (int i = 0; i < total_len; i++)
        transport_wifi_send_byte(buf[i]);
}
#endif
