void system_state_init();

// FSM Enum for system
typedef enum {
    SYS_SAFE,
    SYS_ARMING,
    SYS_ARMED,
    SYS_DISARMED,
    SYS_LOCKOUT
} system_state_t;