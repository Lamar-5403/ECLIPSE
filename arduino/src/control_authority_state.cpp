#include <Arduino.h>
#include "control_authority_state.h"

control_authority_state_t CAS_STATE;

void control_authority_state_init() {
    CAS_STATE = control_authority_state_t::CAS_SAFE;
}