import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SRC = ROOT / "src"

sys.path.append(str(SRC))

import frame
import frame_encoder
import frame_decoder
import crc16_ccitt_false

test_frame = [0] * frame.FRAME_WIRE_SIZE

payload = bytes([0x21, 0x34, 0xC5])
frame_encoder.frame_encode(test_frame, frame.msg_type_t.MSG_HEARTBEAT, payload)

buf = [0] * (5 + frame.FRAME_MAX_PAYLOAD)
frame_encoder.calc_serialized_buf(test_frame, buf)

frame_decoder.frame_decoder_reset()

for b in buf[:3 + test_frame[frame.LEN_OFS] + 2]:
    frame_decoder.frame_decoder_process_byte(b)

crc = (test_frame[frame.CRC_OFS] << 8) | test_frame[frame.CRC_OFS + 1]
payload_hex = ' '.join(f'0x{b:02X}' for b in test_frame[frame.PAYLOAD_OFS : frame.PAYLOAD_OFS + test_frame[frame.LEN_OFS]])

print(f"Frame Received: type: 0x{test_frame[frame.MSG_TYPE_OFS]:02X}, payload = {payload_hex}, CRC: 0x{crc:04X}") 
