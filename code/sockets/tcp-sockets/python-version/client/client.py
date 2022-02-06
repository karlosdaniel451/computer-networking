from socket import *

server_name = input(
    'Enter the server name/address (127.0.0.1 for a server on the localhost): ')
server_port = int(input('Enter the port number listened by the server: '))

# Create the client's socket for TCP over IPv4 and let the Operating System choose a port number.
client_socket = socket(AF_INET, SOCK_STREAM)

# Initiate the TCP connection with the server process.
client_socket.connect((server_name, server_port))
print(f'\nConnection established with server at {server_name}:{server_port}.')

message = input('Input the message to be sent to server: ')

# Send the bytes representing `message` through the client's socket and into the TCP connection.
client_socket.send(message.encode())
print('Message sent to server.')

# Wait to receive bytes from the server.
received_message = client_socket.recv(1024).decode()

print(f'Received message from server: {received_message}')

# Close the client's socket and, hence, close the TCP connection between the client and server.
client_socket.close()
print('Connection closed.')
