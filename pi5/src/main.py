import control_execution_controller
import frame_decoder
import transport_serial
import transport_wifi
import frame

def main():
    print("main entered")
    control_execution_controller.control_execution_controller_init()
    print("controller up")
    frame_decoder.frame_decoder_init()
    print("decoder up")
    transport_serial.transport_serial_init()
    print("serial up")
    #transport_wifi.transport_wifi_init()
    print("System Operational")
    control_execution_controller.arm_system(frame.tactic_code_t.TA_RECON, frame.technique_code_t.T1_ACT_SCAN)
    loop()

def loop():
    while True:
        transport_serial.transport_serial_poll()
        #transport_wifi.transport_wifi_poll()

if __name__ == "__main__":
    main()
