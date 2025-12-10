#include <Arduino.h>
#include "serial_transport.h"
#include "wifi_transport.h"
#include "system_state.h"
#include "frame.h"
#include "controller.h"


void setup() {
  serial_transport_init();
  wifi_transport_init();
  system_controller_init();
}

void loop() {
  // put your main code here, to run repeatedly:
}