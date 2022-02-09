#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

const uint16_t PORT_NUMBER = 12000;
const char *HELLO_WORLD_MESSAGE = "Hello, World!";
const size_t MESSAGE_BUFFER_SIZE = 512;

int main(int argc, char *argv[]) {
    int server_socket_fd;

    struct sockaddr_in server_socket_address;
    struct sockaddr_in client_socket_address;

    socklen_t client_socket_length = sizeof(server_socket_address);

    char received_message[MESSAGE_BUFFER_SIZE];
    ssize_t received_message_length;

    // Try to create a socket for UDP over IPv4.
    server_socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Check that the UDP socket was created succesfully.
    if (server_socket_fd == -1) {
        perror("UDP socket creation error");
        close(server_socket_fd);
        return EXIT_FAILURE;
    }

    puts("UDP socket created successfully.");

    // Set the welcoming TCP socket address information.

    // Set the Address Family to Internet Address Family.
    server_socket_address.sin_family = AF_INET;

    // So that the socket will be bound to all local interfaces.
    server_socket_address.sin_addr.s_addr = htonl(INADDR_ANY);

    // Set the welcoming TCP socket port number.
    server_socket_address.sin_port = htons(PORT_NUMBER);

    // Try to attach the local address (`server_socket_address`) to the
    // server socket and validate it.
    if (bind(server_socket_fd, (struct sockaddr*) &server_socket_address,
             sizeof(server_socket_address)) == -1) {
        perror("UDP socket binding error");
        close(server_socket_fd);
        return EXIT_FAILURE;
    }

    puts("UDP socket bound successfully.");

    // // Try to receive a message from the client and capture its length.
    received_message_length = recvfrom(server_socket_fd, received_message, MESSAGE_BUFFER_SIZE, 0,
                                      (struct sockaddr *) &client_socket_address, &client_socket_length);
    
    if (received_message_length > 0) {
        printf("\nA client process at %s:%u sent the message: %s\n",
               inet_ntoa(client_socket_address.sin_addr),
               htons(client_socket_address.sin_port),
               received_message);
    }

    close(server_socket_fd);
}
