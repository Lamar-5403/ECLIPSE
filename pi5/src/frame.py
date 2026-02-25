global FRAME_START_BYTE, FRAME_MAX_PAYLOAD, FRAME_WIRE_SIZE, frame_t, frame_view
FRAME_START_BYTE = 0xAA
FRAME_MAX_PAYLOAD = 256
FRAME_WIRE_SIZE = 1 + 1 + 1 + FRAME_MAX_PAYLOAD + 2
frame_t = bytearray(FRAME_WIRE_SIZE)
frame_view = memoryview(frame_t)

START_OFS = 0
MSG_TYPE_OFS = 1
LEN_OFS = 2
PAYLOAD_OFS = 3
CRC_OFS = PAYLOAD_OFS + FRAME_MAX_PAYLOAD

class Frame:
    __slots__ = ("buf",)

    def __init__(self):
        self.buf = bytearray(FRAME_WIRE_SIZE)

    @property
    def start(self):
        return self.buf[START_OFS]
    
    @start.setter
    def start(self, v):
        self.buf[START_OFS] = v

    @property
    def msg_type(self):
        return self.buf[MSG_TYPE_OFS]
    
    @msg_type.setter
    def msg_type(self, v):
        self.buf[MSG_TYPE_OFS]

    @property
    def length(self):
        return self.buf[LEN_OFS]
    
    @length.setter
    def length(self, v):
        self.buf[LEN_OFS] = v

    @property
    def payload(self, v):
        self.buf[LEN_OFS] = v;

    def write_payload(self, data):
        n = len(data)
        self.buf[PAYLOAD_OFS:CRC_OFS]
        self.length = n
    
    def set_crc(self, crc):
        self.buf[CRC_OFS] = crc & 0xFF
        self.buf[CRC_OFS + 1] = (crc >> 8) & 0xFF

