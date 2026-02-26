from frame import (frame_t, START_OFS, MSG_TYPE_OFS, LEN_OFS, PAYLOAD_OFS, CRC_OFS, FRAME_MAX_PAYLOAD, FRAME_START_BYTE)
import transport_serial
import transport_wifi
from crc16_ccitt_false import crc16_ccitt_false

def calc_serialized_buf(frame, out):
    length = frame[LEN_OFS]

    out[0] = frame[START_OFS]
    out[1] = frame[MSG_TYPE_OFS]
    out[2] = length

    for i in range (length):
        out[3 + i] = frame[PAYLOAD_OFS + i]
    
    crc = frame[CRC_OFS] << 8 | frame[CRC_OFS + 1]
    out[3 + length] = (crc >> 8) & 0xFF
    out[3 + length + 1] = crc & 0xFF

def frame_encode(frame, type: int, payload: bytes):
    length = len(payload)

    frame[START_OFS] = FRAME_START_BYTE
    frame[MSG_TYPE_OFS] = type
    frame[LEN_OFS] = length

    for i in range(length):
        frame[PAYLOAD_OFS + i] = payload[i]
    
    # frame[PAYLOAD_OFS : PAYLOAD_OFS + length] = payload

    crc = crc16_ccitt_false(bytes(frame[:3 + length]))
    frame[CRC_OFS] = (crc >> 8) & 0xFF
    frame[CRC_OFS + 1] = crc & 0xFF

def send_frame_serial(frame):
    length = frame[LEN_OFS]
    total_len = 3 + length + 2

    buf = [0] * (5 + FRAME_MAX_PAYLOAD)
    calc_serialized_buf(frame, buf)

    for i in range (total_len):
        transport_serial.transport_serial_send_byte(buf[i])

def send_frame_wifi(frame):
    length = frame[LEN_OFS]
    total_len = 3 + length + 2

    buf = [0] * (5 + FRAME_MAX_PAYLOAD)
    calc_serialized_buf(frame, buf)

    for i in range (total_len):
        transport_wifi.transport_wifi_send_byte(buf[i])