import frame_encoder
import transport_wifi
import frame_decoder
import frame
# from frame import frame_t
# from frame import connection_status_t

def control_execution_controller_init():
    # transport_wifi.transport_wifi_register_status_cb(system_controller_wifi_status_cb)
    frame_decoder.frame_decoder_register_handle_frame_cb(system_controller_handle_frame)


def system_controller_handle_frame(rx_frame):
    ################################################################################################
    # TEST PURPOSES ONLY
    if rx_frame.type == frame.msg_type_t.MSG_STATUS_RESPONSE:
        if rx_frame.payload[0] == 0x56 and rx_frame.payload[1] == 0x78:
            crc = (rx_frame[frame.CRC_OFS] << 8) | rx_frame[frame.CRC_OFS + 1]
            print(
                "Frame received: type: 0x{:02X}, payload: 0x{:02X} 0x{:02X}, crc: 0x{04X}".format(
                    rx_frame.type,
                    rx_frame.payload[0],
                    rx_frame.payload[1],
                    crc
                )
            )
    # TEST PURPOSES ONLY
    ################################################################################################

# def system_controller_wifi_status_cb(connection_status_t status):
#     if status == (connection_status_t): WIFI_DISCONNECTED
        # degrade 