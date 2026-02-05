#pragma once
#include "frame.h"
#include "frame_encoder.h"
#include "control_authority_state.h"
#include "life_cycle_state.h"

struct frame_t;

void system_controller_handle_frame(frame_t*);
void report_status(connection_status_t);