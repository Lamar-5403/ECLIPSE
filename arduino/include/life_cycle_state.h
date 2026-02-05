enum class life_cycle_state_t {
    BOOTSTRAP, 
    OPERATIONAL,
    DEGRADED,
    FAULT
};

void life_cycle_state_init();
void set_life_cycle_state(life_cycle_state_t);