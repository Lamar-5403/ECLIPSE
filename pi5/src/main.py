import frame
import transport_serial
import transport_wifi
import frame_decoder
import control_execution_controller

def main():
    control_execution_controller.control_execution_controller_init()
    frame_decoder.frame_decoder_init()
    transport_serial.transport_serial_init()
    transport_wifi.transport_wifi_init()
    print("System Operational")
    loop()

def loop():
    while True:
        transport_serial.transport_serial_poll()
        transport_wifi.transport_wifi_poll()
