from frame import frame_decoder_state
from crc16_ccitt_false import crc16_ccitt_false
import transport_serial
import transport_wifi
from frame import (
    frame_t,
    START_OFS,
    MSG_TYPE_OFS,
    LEN_OFS,
    PAYLOAD_OFS,
    CRC_OFS,
    FRAME_WIRE_SIZE,
    FRAME_START_BYTE
)

_handle_frame_cb = None

def frame_decoder_register_handle_frame_cb(cb):
    global _handle_frame_cb
    _handle_frame_cb = cb

global state 
state = frame_decoder_state.WAIT_START

def frame_decoder_init():
    frame_decoder_reset()
    transport_serial.transport_serial_register_decoder_reset_cb(frame_decoder_reset)
    transport_serial.transport_serial_register_process_byte_cb(frame_decoder_process_byte)
    transport_wifi.transport_wifi_register_process_byte_cb(frame_decoder_process_byte)
    transport_wifi.transport_wifi_register_decoder_reset_cb(frame_decoder_reset)

def frame_decoder_reset():
    # reset frame decoder FSM
    global state, payload_index, crc_calc, crc_idx
    state = frame_decoder_state.WAIT_START
    payload_index = 0
    crc_calc = 0
    crc_idx = 0

def frame_decoder_process_byte(b: int):
    global state, payload_index, crc_idx, crc_calc
    match state:
        case frame_decoder_state.WAIT_START:
            if b != FRAME_START_BYTE:
                return
            else:
                frame_t[START_OFS] = FRAME_START_BYTE
                state = frame_decoder_state.READ_TYPE
        
        case frame_decoder_state.READ_TYPE:
            frame_t[MSG_TYPE_OFS] = b
            state = frame_decoder_state.READ_LEN

        case frame_decoder_state.READ_LEN:
            frame_t[LEN_OFS] = b
            state = frame_decoder_state.READ_CRC if b == 0 else frame_decoder_state.READ_PAYLOAD

        case frame_decoder_state.READ_PAYLOAD:
            frame_t[PAYLOAD_OFS + payload_index] = b
            payload_index += 1
            if payload_index == frame_t[LEN_OFS]:
                state = frame_decoder_state.READ_CRC
            else:
                return

        case frame_decoder_state.READ_CRC:
            if crc_idx == 0:
                frame_t[CRC_OFS] = b
                crc_idx += 1
            else:
                frame_t[CRC_OFS + 1] = b
                crc_idx = 0
                # calculate and compare crc16 value to validate frame
                crc_calc = crc16_ccitt_false(frame_t[START_OFS : START_OFS + 3 + frame_t[LEN_OFS]])
                stored_crc = (frame_t[CRC_OFS] << 8) | frame_t[CRC_OFS + 1]
                if crc_calc == stored_crc:
                    if _handle_frame_cb is not None:
                        _handle_frame_cb(frame_t)
                frame_decoder_reset()

        case _:
            # Invalid decoder state unreachable outside of system level error
            # Send failure to authoritative controller to transisiton to FAULT
            pass