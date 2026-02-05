#include "life_cycle_state.h"

life_cycle_state_t system_lifecycle;

void life_cycle_state_init() {
    life_cycle_state_t system_lifecycle = life_cycle_state_t::BOOTSTRAP;
}

void set_life_cycle_state(life_cycle_state_t new_state) {
    system_lifecycle = new_state;
}