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

# MITRE ATT&CK tactic codes
class tactic_code_t(IntEnum):
    TA_RECON            = 0x43
    TA_INIT_ACS         = 0x01
    TA_PRIV_ESC         = 0x04
    TA_CRED_ACS         = 0x06
    TA_DISCO            = 0x07
    TA_LAT_MOV          = 0x08
    TA_COMM_CONT        = 0x11

# MITRE ATT&CK technique codes
class technique_code_t(IntEnum):
    T1_ACT_SCAN         = 0x01
    T1_SERV_ENUM        = 0x02
    T1_EXP_PUB_APP      = 0x03
    T1_BRUT_FRCE        = 0x04
    T1_REM_SYS_DIS      = 0x05
    T1_NET_SERV_DIS     = 0x06

# Decoder states
class frame_decoder_state(IntEnum):
    WAIT_START          = 0x01
    READ_TYPE           = 0x02
    READ_LEN            = 0x03
    READ_PAYLOAD        = 0x04
    READ_CRC            = 0x05

# Wifi Connection statuses
class connection_status_t(IntEnum):
    WIFI_UNINITIALIZED  = 0x01
    WIFI_CONNECTING     = 0x02
    WIFI_CONNECTED      = 0x03
    WIFI_DISCONNECTED   = 0x04
    WIFI_FAILED         = 0x05

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