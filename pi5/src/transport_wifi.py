# creating a simple tcp ip server
import socket

# create a tcp/ip socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# bind socket to port for server
server_addr = ('', 5238)
print("Starting up on %s port %s" % server_addr)
sock.bind((server_addr))

# listen for inbound connections
sock.listen(1)

while True:
    # wait for connection
    print("waiting for connection")
    connection, client_addr = sock.accept()

    try:
        print("connection from ", client_addr)
        # receive the data in chunks of bytes
        while True:
            data = connection.recv(1600)
            print("received '%s'" % data)
            if data:
                print("sending data back to client")
                msg = str(data)
                msg = msg + " plus extra from server"
                msg = bytes(msg, 'utf-8')
                connection.sendall(msg)
            else:
                print("no more data from ", client_addr)
                connection.close()
                break
    finally:
        # clean up code
        connection.close()