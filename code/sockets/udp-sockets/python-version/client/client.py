from socket import *

BUFFER_SIZE = 2048

server_name = input(
    'Enter the server name/address (127.0.0.1 for a server on the localhost): ')
server_port = int(input('Enter the port number of the server\'s socket: '))

server_address_info = (server_name, server_port)


# Create the client's socket for UDP over IPv4 and let the Operating System choose a port number.
client_socket = socket(AF_INET, SOCK_DGRAM)

message = input('\nInput the message to be sent to the server: ')

# Send the bytes representing `message` through the client's socket to the
# server process whose used socket corresponds to `server_address_info`.
client_socket.sendto(message.encode(), server_address_info)
print('Message sent to server (there is no guarantee that it will receive it'
      ' correctly, nor that it will receive it at all.')

# Wait to receive bytes from the server process.
received_message = client_socket.recvfrom(BUFFER_SIZE)
print(f'\nReceived message from server: {received_message[0].decode()}')

client_socket.close()
