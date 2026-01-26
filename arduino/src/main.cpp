#include <Arduino.h>
#include "transport_serial.h"
#include "transport_wifi.h"
#include "system_controller.h"
#include "system_state.h"

enum class life_cycle_state_t {
  BOOTSTRAP, 
  OPERATIONAL,
  DEGRADED,
  FAULT
};

life_cycle_state_t system_lifecycle = life_cycle_state_t::BOOTSTRAP;


void setup() {
  transport_serial_init();
  transport_wifi_init();
  system_state_init();

  system_lifecycle = life_cycle_state_t::OPERATIONAL;
}

void loop() {
  transport_serial_poll();
  transport_wifi_poll();
}