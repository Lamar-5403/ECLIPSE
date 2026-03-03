import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"

sys.path.append(str(SRC))

import frame
from frame import Frame, FRAME_MAX_PAYLOAD
import frame_encoder
import frame_decoder
import control_execution_controller
import transport_serial

control_execution_controller.control_execution_controller_init()
frame_decoder.frame_decoder_init()
transport_serial.transport_serial_init()

test_frame = Frame(
    start=0,
    type=None,
    length=0,
    payload=bytearray[FRAME_MAX_PAYLOAD],
    crc=0
)

payload = bytes([0xAC, 0xDC])
frame_encoder.frame_encode(test_frame, frame.msg_type_t.MSG_STATUS_REQUEST, payload)

buf = [0] * (5 + frame.FRAME_MAX_PAYLOAD)
frame_encoder.calc_serialized_buf(test_frame, buf)

for b in buf[:3 + test_frame.len + 2]:
    transport_serial.transport_serial_send_byte(b)
    time.sleep(0.002)

while True:
    transport_serial.transport_serial_poll()