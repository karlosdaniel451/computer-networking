from socket import *

BUFFER_SIZE = 2048
SERVER_SOCKET_PORT = 12000

# Create the server's socket for UDP over IPv4.
server_socket = socket(AF_INET, SOCK_DGRAM)

# Assign the port number to the server's socket.
server_socket.bind(('', SERVER_SOCKET_PORT))
print(f'The server is ready to receive messages from its socket at localhost:'
      f'{SERVER_SOCKET_PORT}')

while 1:
    # Wait to receive bytes from the client process.
    received_message, client_address = server_socket.recvfrom(BUFFER_SIZE)
    print(f'\nReceived message from client at {client_address[0]}:'
          f'{client_address[1]}: {received_message.decode()}')

    capitalized_sentence = received_message.upper()

    # Send the bytes representing the `capitalized_sequence` to the client process
    server_socket.sendto(capitalized_sentence, client_address)
    print(f'Message sent to client: {capitalized_sentence.decode()}')
