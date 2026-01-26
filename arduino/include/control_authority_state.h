#pragma once
void control_authority_state_init();

// FSM Enum for system
enum class control_authority_state_t {
    CAS_SAFE,
    CAS_ARMING,
    CAS_ARMED,
    CAS_DISARMED,
    CAS_LOCKOUT
};