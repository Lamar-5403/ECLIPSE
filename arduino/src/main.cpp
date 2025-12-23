#include <Arduino.h>
#include "transport_serial.h"
#include "transport_wifi.h"
#include "system_state.h"
#include "frame.h"
#include "system_controller.h"
#include "system_state.h"


void setup() {
  transport_serial_init();
  transport_wifi_init();
  system_state_init();
}

void loop() {
  transport_serial_poll();
  transport_wifi_poll();
}