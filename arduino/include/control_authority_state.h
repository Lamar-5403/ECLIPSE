#pragma once
void control_authority_state_init();
void set_control_authority_state(control_authority_state_t);

// FSM Enum for system
enum class control_authority_state_t {
    CAS_SAFE,
    CAS_ARMING,
    CAS_ARMED,
    CAS_DISARMED,
    CAS_LOCKOUT
};