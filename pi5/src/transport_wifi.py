import socket
import select
from frame_decoder import frame_decoder_reset, frame_decoder_process_byte

def transport_wifi_init():
    global sock, connection, client_addr
    server_addr = "127.0.0.1", 45434
    
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind((server_addr))
    sock.listen(1)
    connection, client_addr = sock.accept()
    frame_decoder_reset()


def transport_wifi_poll():
    global connection
    readable, _, _ = select.select([connection], [], [], 0)
    if not readable:
        return
    
    data = connection.recv(1600)
    if not data:
        #connection.close()
        return
    
    for byte in data:
        frame_decoder_process_byte(byte)

def transport_wifi_write_bytes(frame: bytes):
    connection.sendall(frame)