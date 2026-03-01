import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"

sys.path.append(str(SRC))

import frame
import frame_encoder
import frame_decoder
import control_execution_controller
import transport_serial

control_execution_controller.control_execution_controller_init()
frame_decoder.frame_decoder_init()
transport_serial.transport_serial_init()

test_frame = [0] * frame.FRAME_WIRE_SIZE

payload = bytes([0xAC, 0xDC])
frame_encoder.frame_encode(test_frame, frame.msg_type_t.MSG_STATUS_REQUEST, payload)

buf = [0] * (5 + frame.FRAME_MAX_PAYLOAD)
frame_encoder.calc_serialized_buf(test_frame, buf)

for b in buf[:3 + test_frame[frame.LEN_OFS] + 2]:
    transport_serial.transport_serial_send_byte(b)

while True:
    transport_serial.transport_serial_poll()

# print(f"Frame Received: type: 0x{test_frame[frame.MSG_TYPE_OFS]:02X}, payload = {payload_hex}, CRC: 0x{crc:04X}") 
