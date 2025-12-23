#include <Arduino.h>
#include "transport_serial.h"
#include "frame_decoder.h"
#include <cstdint>
#include "frame.h"

void transport_serial_init() {
    Serial.begin(115200); 
}

void transport_serial_poll() {
    if (Serial.available() > 0) {
        frame_decoder_process_byte(Serial.read());
    }
}

void transport_serial_send_byte(const uint8_t* byte, size_t size) {
    Serial.write(byte, size);
}