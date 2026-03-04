from frame import (Frame, FRAME_MAX_PAYLOAD, FRAME_START_BYTE)
import transport_serial
import transport_wifi
from crc16_ccitt_false import crc16_ccitt_false

def calc_serialized_buf(frame: Frame, out):
    length = frame.length

    out[0] = frame.start
    out[1] = frame.type
    out[2] = length

    for i in range (length):
        out[3 + i] = frame.payload[i]
    
    crc = frame.crc
    out[3 + length] = (crc >> 8) & 0xFF
    out[3 + length + 1] = crc & 0xFF

def frame_encode(frame: Frame, type: int, payload: bytes):
    length = len(payload)

    frame.start = FRAME_START_BYTE
    frame.type = type
    frame.length = length
    frame.write_payload(payload)

    crc_input = bytes([
                    frame.start,
                    int(frame.type),
                    frame.length,
                    *frame.payload[:frame.length]
                ])
    crc = crc16_ccitt_false(crc_input)
    frame.set_crc(crc)

def send_frame_serial(frame: Frame):
    length = frame.length
    total_len = 3 + length + 2

    buf = [0] * (5 + FRAME_MAX_PAYLOAD)
    calc_serialized_buf(frame, buf)

    for i in range (total_len):
        transport_serial.transport_serial_send_byte(buf[i])

def send_frame_wifi(frame: Frame):
    length = frame.length
    total_len = 3 + length + 2

    buf = [0] * (5 + FRAME_MAX_PAYLOAD)
    calc_serialized_buf(frame, buf)

    for i in range (total_len):
        transport_wifi.transport_wifi_send_byte(buf[i])