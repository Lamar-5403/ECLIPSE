import frame_encoder
import transport_serial
import frame_decoder
import frame
from frame import Frame, tactic_code_t, technique_code_t, FRAME_MAX_PAYLOAD
import json
from datetime import datetime, timezone
from attack_discovery import discover_hosts
from attack_port_scanner import scan_ports
from attack_service_enum import enumerate_services
from attack_vuln_mapper import map_vuln
from attack_planner import plan_attack

def control_execution_controller_init():
    # transport_wifi.transport_wifi_register_status_cb(system_controller_wifi_status_cb)
    frame_decoder.frame_decoder_register_handle_frame_cb(system_controller_handle_frame)

def system_controller_handle_frame(rx_frame):
    print("frame handler entered")
    ################################################################################################
    # TEST PURPOSES ONLY
    if rx_frame.type == frame.msg_type_t.MSG_STATUS_RESPONSE:
        if rx_frame.payload[0] == 0x56 and rx_frame.payload[1] == 0x78:
            print(
                "Frame received: type: 0x{:02X}, payload: 0x{:02X} 0x{:02X}, crc: 0x{:04X}".format(
                    rx_frame.type,
                    rx_frame.payload[0],
                    rx_frame.payload[1],
                    rx_frame.crc
                )
            )
        
        if rx_frame.payload[0] == 0x03:
            execute_recon()
    # TEST PURPOSES ONLY
    ################################################################################################


# def system_controller_wifi_status_cb(connection_status_t status):
#     if status == (connection_status_t): WIFI_DISCONNECTED
        # degrade 

def execute_recon():
    timestamp = datetime.now(timezone.utc).isoformat()
    filename = f"scan_{datetime.now(timezone.utc).strftime('%Y%m%d_%H%M%S')}.json"
    data = discover_hosts("192.168.56.0/24")
    data = scan_ports(data)
    data = enumerate_services(data)
    data = map_vuln(data)
    data = plan_attack(data)
    log_entry = {
        "timestamp": timestamp,
        "data": data
    }
    with open(filename, "w") as f:
        json.dump(log_entry, f, indent=4)
    print(data)

def arm_system(tactic: frame.tactic_code_t, technique: frame.technique_code_t):
    arm_frame = Frame(
        start=0,
        type=frame.msg_type_t.MSG_ARM,
        length=0,
        payload=bytearray(FRAME_MAX_PAYLOAD),
        crc=0
    )

    payload = bytearray([tactic.value, technique.value])

    frame_encoder.frame_encode(arm_frame, frame.msg_type_t.MSG_ARM, payload)

    buf = [0] * (frame.FRAME_WIRE_SIZE)
    frame_encoder.calc_serialized_buf(arm_frame, buf)

    if arm_frame.length > FRAME_MAX_PAYLOAD:
        raise ValueError("Payload too large")

    for b in buf[:3 + arm_frame.length + 2]:
        transport_serial.transport_serial_send_byte(b)