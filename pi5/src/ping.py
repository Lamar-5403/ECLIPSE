import serial
import time

ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
ser.flush()

ser.write(b'ping\n')        # Send test message
line = ser.readline().decode('utf-8').rstrip()
print(line)

