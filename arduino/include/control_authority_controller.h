#pragma once
#include "frame_encoder.h"
#include "control_authority_state.h"
#include "life_cycle_state.h"
#include "types.h"

struct frame_t;

// void system_controller_wifi_status_cb(connection_status_t);
void system_controller_handle_frame_cb(frame_t*);

bool tactic_allowed(uint8_t);
bool technique_allowed(uint8_t);
bool cooldown_ready(uint8_t);

void control_authority_controller_init();