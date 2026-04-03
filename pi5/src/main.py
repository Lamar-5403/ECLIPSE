import control_execution_controller
import frame_decoder
import transport_serial
# import transport_wifi
import frame

def main():
    control_execution_controller.control_execution_controller_init()
    frame_decoder.frame_decoder_init()
    transport_serial.transport_serial_init()
    control_execution_controller.arm_system(frame.tactic_code_t.TA_RECON, frame.technique_code_t.T1_ACT_SCAN)
    loop()

def loop():
    while True:
        transport_serial.transport_serial_poll()

if __name__ == "__main__":
    main()
