#include <Arduino.h>
#include "transport_serial.h"
#include "transport_wifi.h"
#include "control_authority_controller.h"
#include "control_authority_state.h"
#include "life_cycle_state.h"




void setup() {
  life_cycle_state_init();
  control_authority_state_init();
  transport_serial_init();
  transport_wifi_init();

  set_life_cycle_state(life_cycle_state_t::OPERATIONAL);
}

void loop() {
  transport_serial_poll();
  transport_wifi_poll();
}