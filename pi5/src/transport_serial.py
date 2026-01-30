import serial
import time

global ser

def transport_serial_init():
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
    ser.flush()

def transport_serial_send_byte():
    ser.write()