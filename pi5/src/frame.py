from enum import IntEnum
global FRAME_START_BYTE, FRAME_MAX_PAYLOAD, FRAME_WIRE_SIZE

FRAME_START_BYTE = 0xAA
FRAME_MAX_PAYLOAD = 256
FRAME_WIRE_SIZE = 1 + 1 + 1 + FRAME_MAX_PAYLOAD + 2

START_OFS = 0
MSG_TYPE_OFS = 1
LEN_OFS = 2
PAYLOAD_OFS = 3
CRC_OFS = PAYLOAD_OFS + FRAME_MAX_PAYLOAD

# MSG type architecture
class msg_type_t(IntEnum):
    MSG_ARM             = 0x01
    MSG_DISARM          = 0x02
    MSG_STATUS_REQUEST  = 0x03
    MSG_STATUS_RESPONSE = 0x04
    MSG_HEARTBEAT       = 0x05

# Decoder states
class frame_decoder_state(IntEnum):
    WAIT_START          = 0
    READ_TYPE           = 1
    READ_LEN            = 2
    READ_PAYLOAD        = 3
    READ_CRC            = 4

# Wifi Connection statuses
class connection_status_t(IntEnum):
    WIFI_UNINITIALIZED  = 0
    WIFI_CONNECTING     = 1
    WIFI_CONNECTED      = 2
    WIFI_DISCONNECTED   = 3
    WIFI_FAILED         = 4

class Frame:
    __slots__ = ("start", "type", "length", "payload", "crc")

    def __init__(self, start, type: msg_type_t, length, payload, crc):
        self.start = start
        self.type = type
        self.length = length
        self.payload = payload if payload is not None else bytearray(FRAME_MAX_PAYLOAD)
        self.crc = crc

    def write_payload(self, data: bytes):
        n = len(data)
        self.payload[:n] = data
        self.length = n

    def set_crc(self, crc: int):
        self.crc = crc