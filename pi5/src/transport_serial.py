import serial
from serial.tools import list_ports

def arduino_port_discovery():
    for port in list_ports.comports():
        if "Arduino" in port.description or "CDC" in port.description or "ACM" in port.device:
            return port.device
    raise RuntimeError("Arduino port not found")

_process_byte_cb = None
_decoder_reset_cb = None
_ser = None

def transport_serial_register_process_byte_cb(cb):
    global _process_byte_cb
    _process_byte_cb = cb

def transport_serial_register_decoder_reset_cb(cb):
    global _decoder_reset_cb
    _decoder_reset_cb = cb

def transport_serial_init():
    global _ser
    _ser = serial.Serial(arduino_port_discovery(), 115200, timeout=1)

def transport_serial_poll():
    if _decoder_reset_cb is not None:
        _decoder_reset_cb()

    while _ser.in_waiting > 0:
        if _process_byte_cb is not None:
            _process_byte_cb(_ser.read(1))


def transport_serial_send_byte(b: int):
    _ser.write(bytes([b]))
