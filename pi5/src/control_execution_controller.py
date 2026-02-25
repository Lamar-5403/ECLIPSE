import frame_encoder
import transport_wifi
import frame_decoder
from frame import frame_t

frame = frame_t

def control_execution_controller_init():
    transport_wifi.transport_wifi_register_status_cb(system_controller_wifi_status_cb)
    frame_decoder.frame_decoder_register_handle_frame_cb(system_controller_handle_frame)


def system_controller_handle_frame():
    pass

def system_controller_wifi_status_cb(connection_status_t status):
    if status == connection_status_t::WIFI_DISCONNECTED
        # degrade 