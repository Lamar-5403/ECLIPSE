#include <Arduino.h>
#include "../include/transport_serial.h"

static process_byte_cb_t process_byte_cb = nullptr;
static frame_decoder_reset_cb_t frame_decoder_reset_cb = nullptr;

void test_transport_serial_register_process_byte_cb(process_byte_cb_t cb) {
    process_byte_cb = cb;
}

void test_transport_serial_register_decoder_reset_cb(frame_decoder_reset_cb_t cb) {
    frame_decoder_reset_cb = cb;
}

void transport_serial_init() {
    Serial.begin(115200); 
}

void transport_serial_poll() {
    if (frame_decoder_reset_cb) {
        frame_decoder_reset_cb();
    }
    while (Serial.available() > 0) {
        if (process_byte_cb) {
            process_byte_cb(Serial.read());
        }
    }
}

void transport_serial_send_byte(const uint8_t byte) {
    Serial.write(byte);
}