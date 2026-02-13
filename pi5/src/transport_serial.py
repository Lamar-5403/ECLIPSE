import serial
from serial.tools import list_ports
# from frame_decoder import frame_decoder_reset, frame_decoder_process_byte

def arduino_port_discovery():
    for port in list_ports.comports():
        if "Arduino" in port.description or "CDC" in port.description or "ACM" in port.device:
            return port.device
    raise RuntimeError("Arduino port not found")

def transport_serial_init():
    global _ser
    _ser = serial.Serial(arduino_port_discovery(), 115200, timeout=1)
    _ser.flush()

def transport_serial_poll():
    # frame_decoder_reset()
    while _ser.in_waiting > 0:
        pass #frame_decoder_process_byte(_ser.read())


def transport_serial_send_byte(b: int):
    _ser.write(bytes([b]))
    _ser.flush()
