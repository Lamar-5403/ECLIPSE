#include "transport_serial.h"
#include <Arduino.h>

static process_byte_cb_t process_byte_cb = nullptr;

void transport_serial_register_process_byte_cb(process_byte_cb_t cb) {
    process_byte_cb = cb;
}

void transport_serial_init() {
    Serial.begin(115200); 
}

void transport_serial_poll() {
    //frame_decoder_reset();
    while (Serial.available() > 0) {
        //callback hook
        if (process_byte_cb) {
            process_byte_cb(Serial.read());
        }
    }
}

void transport_serial_send_byte(const uint8_t* byte, size_t size) {
    Serial.write(byte, size);
    Serial.flush();
}