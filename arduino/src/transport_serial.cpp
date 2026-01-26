#include "transport_serial.h"
#include <Arduino.h>
#include "frame_decoder.h"

void transport_serial_init() {
    Serial.begin(115200); 
    while (!Serial);
}

void transport_serial_poll() {
    while (Serial.available() > 0) {
        frame_decoder_process_byte(Serial.read());
    }
}

void transport_serial_send_byte(const uint8_t* byte, size_t size) {
    Serial.write(byte, size);
    Serial.flush();
}