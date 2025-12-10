#include <Arduino.h>
#include "serial_transport.h"

void serial_transport_init() {
    Serial.begin(115200);
}