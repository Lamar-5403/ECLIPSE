from frame import (frame_t, START_OFS, MSG_TYPE_OFS, LEN_OFS, PAYLOAD_OFS, CRC_OFS)

def encode_frame(frame_t, start: int, type: int, length: int, payload: bytes, crc: bytes):
    frame_t[START_OFS] = start
    frame_t[MSG_TYPE_OFS] = type
    frame_t[LEN_OFS] = length
    frame_t[PAYLOAD_OFS : PAYLOAD_OFS + length] = payload
    frame_t[CRC_OFS : CRC_OFS + 2] = crc