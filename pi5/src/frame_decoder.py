from enum import Enum, auto

class frame_decoder_state(Enum):
    WAIT_START = auto()
    READ_TYPE = auto()
    READ_LEN = auto()
    READ_PAYLOAD = auto()
    READ_CRC = auto()

global state 

state = frame_decoder_state.WAIT_START

# example parser
match state:
    case frame_decoder_state.WAIT_START:
        # do something
        print("Waiting for start...")
    
    case frame_decoder_state.READ_TYPE:
        # do something
        print("Waiting for type...")

    case frame_decoder_state.READ_LEN:
        # do something
        print("Waiting for len...")

    case frame_decoder_state.READ_PAYLOAD:
        # do something
        print("Waiting for payload...")

    case frame_decoder_state.READ_CRC:
        # do something
        print("Waiting for crc...")

    case _:
        # do something
        print("Waiting for something amazing i guess...")

def frame_decoder_reset():
    # reset frame decoder FSM
    global state
    state = frame_decoder_state.WAIT_START