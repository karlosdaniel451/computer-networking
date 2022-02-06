from socket import *

port_number_to_bind = 12000

# Create the client's socket for TCP over IPv4 and let the Operating System choose a port number.
welcoming_socket = socket(AF_INET, SOCK_STREAM)

# Allow the process to bind to a port number which remains in TIME_WAIT.
# This is both the simplest and them most effective option for reducing the
# "Address already in use" error.
# Source: https://hea-www.harvard.edu/~fine/Tech/addrinuse.html
welcoming_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)

# Associate the port number with the socket.
welcoming_socket.bind(('', port_number_to_bind))

# Wait and listen for contact from some client to establish a TCP connection.
# The single parameter specifies the maximum number of queued connections.
welcoming_socket.listen(1)

print('The server is ready to receive a TCP connection request from some client.')

while 1:
    # Accept a TCP connection request from a client process and create a new
    # socket to this particular connection.
    connection_socket, address = welcoming_socket.accept()
    print(f'\nConnection established with client at {address[0]}:{address[1]}.')

    # Wait to receive bytes from the client.
    received_message = connection_socket.recv(1024).decode()
    print(f'Received message from client: {received_message}')

    capitalized_sentence = received_message.upper()

    # Send the bytes representing the `capitalized_sequence` to the client.
    connection_socket.send(capitalized_sentence.encode())
    print(f'Message sent to server: {capitalized_sentence}')

    # Close the socket for the particular client.
    connection_socket.close()
    print('Connection closed.')

