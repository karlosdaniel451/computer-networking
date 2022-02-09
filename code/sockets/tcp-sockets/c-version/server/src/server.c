// Reference: https://riptutorial.com/posix/example/22276/socket-basics.

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

const int PORT_NUMBER = 12000;
const int CONNECTION_REQUEST_QUEUE_LENGTH = 1;
const size_t MESSAGE_BUFFER_SIZE = 512;

int main(int argc, char *argv[]) {
    int welcoming_socket_fd;
    int connection_socket_fd;

    struct sockaddr_in welcoming_socket_address;
    struct sockaddr_in connection_socket_address;

    char received_message[MESSAGE_BUFFER_SIZE];
    ssize_t received_message_length;

    // Try to creat the welcoming socket for TCP over IPv4.
    welcoming_socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Check that the welcoming TCP socket was created succesfully.
    if (welcoming_socket_fd == -1) {
        perror("TCP socket creation error");
        close(welcoming_socket_fd);
        return EXIT_FAILURE;
    }

    puts("Welcoming TCP socket created successfully.");

    // Set the welcoming TCP socket address information.

    // Set the Address Family to Internet Address Family.
    welcoming_socket_address.sin_family = AF_INET;

    // So that the socket will be bound to all local interfaces.
    welcoming_socket_address.sin_addr.s_addr = htonl(INADDR_ANY);

    // Set the welcoming TCP socket port number.
    welcoming_socket_address.sin_port = htons(PORT_NUMBER);

    // Try to attach the local address (`welcoming_socket_address`) to the
    // welcoming socket and validate it.
    if (bind(welcoming_socket_fd, (struct sockaddr *)&welcoming_socket_address,
             sizeof(welcoming_socket_address)) == -1) {
        perror("Welcoming TCP socket binding error");
        close(welcoming_socket_fd);
        return EXIT_FAILURE;
    }

    puts("Welcoming TCP socket bound successfully.");

    // Try to listen for TCP connections requests and validate it.
    if (listen(welcoming_socket_fd, CONNECTION_REQUEST_QUEUE_LENGTH) == -1) {
        perror("Socket listening error");
        close(welcoming_socket_fd);
        return EXIT_FAILURE;
    }

    printf("Listening for TCP connection requests at port %d...\n", PORT_NUMBER);

    // Try to accept a TCP connection and create a new socket for this connection.
    socklen_t client_socket_length = sizeof(connection_socket_address);
    connection_socket_fd = accept(welcoming_socket_fd, (struct sockaddr *)&connection_socket_address,
                                  &client_socket_length);

    // Validate the connection accepting.
    if (connection_socket_fd == -1) {
        perror("Accept error");
        close(welcoming_socket_fd);
        close(connection_socket_fd);
        return EXIT_FAILURE;
    }

    printf("\nTCP connection established with client at %s:%d.\n",
           inet_ntoa(connection_socket_address.sin_addr),
           connection_socket_address.sin_port);

    // Try to receive a message from the socket and capture its length.
    received_message_length =  recv(connection_socket_fd, received_message, MESSAGE_BUFFER_SIZE, 0);

    // Validate length of the received message.
    if (received_message_length < 0) {
        perror("Error by receiving a message");
        close(welcoming_socket_fd);
        close(connection_socket_fd);
        return EXIT_FAILURE;
    }
    if (received_message_length == 0) {
        fprintf(stderr, "Client orderly shut down the connection.\n");
        close(welcoming_socket_fd);
        close(connection_socket_fd);
        return EXIT_SUCCESS;
    }

    printf("\nReceived message from process at %s:%d:\n",
           inet_ntoa(connection_socket_address.sin_addr),
           connection_socket_address.sin_port);
    write(STDOUT_FILENO, received_message, received_message_length);
    puts("\n");

    // Release the allocated resources to the socket.
    close(welcoming_socket_fd);
    close(connection_socket_fd);

    return EXIT_SUCCESS;
}
