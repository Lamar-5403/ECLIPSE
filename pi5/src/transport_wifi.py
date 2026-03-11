import socket
import select

_process_byte_cb = None
_decoder_reset_cb = None
_status_cb = None

def transport_wifi_register_process_byte_cb(cb):
    global _process_byte_cb
    _process_byte_cb = cb

def transport_wifi_register_decoder_reset_cb(cb):
    global _decoder_reset_cb
    _decoder_reset_cb = cb

# def transport_wifi_register_status_cb(cb):
#     _status_cb = cb

def transport_wifi_init():
    global sock, connection, client_addr
    server_addr = "127.0.0.1", 45434
    
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind((server_addr))
    sock.listen(1)
    connection, client_addr = sock.accept()


def transport_wifi_poll():
    global connection
    readable, _, _ = select.select([connection], [], [], 0)
    if not readable:
        return
    
    data = connection.recv(1600)
    if not data:
        return
    
    if _process_byte_cb is not None:
        for byte in data:
            _process_byte_cb(byte)

def transport_wifi_write_bytes(b: int):
    connection.send(bytes[b])