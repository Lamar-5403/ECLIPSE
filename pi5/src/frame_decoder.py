from frame import frame_decoder_state
from crc16_ccitt_false import crc16_ccitt_false
import transport_serial
import transport_wifi
from frame import (
    Frame,
    FRAME_START_BYTE,
    FRAME_MAX_PAYLOAD,
    msg_type_t
)

rx_frame = Frame(
    start=0,
    type=None,
    length=0,
    payload=bytearray(FRAME_MAX_PAYLOAD),
    crc=0
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
                rx_frame.start = FRAME_START_BYTE
                state = frame_decoder_state.READ_TYPE
        
        case frame_decoder_state.READ_TYPE:
            rx_frame.type = msg_type_t(b)
            state = frame_decoder_state.READ_LEN

        case frame_decoder_state.READ_LEN:
            rx_frame.length = b
            state = frame_decoder_state.READ_CRC if b == 0 else frame_decoder_state.READ_PAYLOAD

        case frame_decoder_state.READ_PAYLOAD:
            rx_frame.payload[payload_index] = b
            payload_index += 1
            if payload_index == rx_frame.length:
                state = frame_decoder_state.READ_CRC
            else:
                return

        case frame_decoder_state.READ_CRC:
            if crc_idx == 0:
                rx_frame.crc = b << 8
                crc_idx = 1
                return
            else:
                rx_frame.crc |= b
                crc_idx = 0
                # calculate and compare crc16 value to validate frame
                crc_input = bytes([
                    rx_frame.start,
                    int(rx_frame.type),
                    rx_frame.length,
                    *rx_frame.payload[:rx_frame.length]
                ])
                crc_calc = crc16_ccitt_false(crc_input)
                if crc_calc == rx_frame.crc:
                    if _handle_frame_cb is not None:
                        _handle_frame_cb(rx_frame)
                frame_decoder_reset()

        case _:
            # Invalid decoder state unreachable outside of system level error
            # Send failure to authoritative controller to transisiton to FAULT
            pass