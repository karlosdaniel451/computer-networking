#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

const char *SERVER_IP_ADDRESS = "127.0.0.1";
const int SERVER_PORT_NUMBER = 12000;
const size_t MAXIMUM_BUFFER_LENGTH = 512;

int main(int argc, char *argv[]) {
    int client_socket_fd;

    struct sockaddr_in client_socket_address;
    struct sockaddr_in server_socket_address;

    char *hello_world_message = "Hello, World!";

    // Try to create a socket for UDP over IPv4.
    client_socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // Check that the UDP socket was created succesfully.
    if (client_socket_fd == -1) {
        perror("UDP socket creation error");
        close(client_socket_fd);
        return EXIT_FAILURE;
    }

    puts("UDP socket created successfully.");

    // Set the address of the server's socket.
    server_socket_address.sin_family = AF_INET;
    server_socket_address.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);
    server_socket_address.sin_port = htons(SERVER_PORT_NUMBER);

    // Try to send a message to the server and validate it.
    if (sendto(client_socket_fd, hello_world_message,
               strlen(hello_world_message), 0,
               (struct sockaddr *)&server_socket_address,
               sizeof(server_socket_address)) == -1) {
        
        perror("Error by trying to send message");
        close(client_socket_fd);
        return EXIT_FAILURE;
    }
    
    printf("Message sent to process at %s:%d: %s\n", SERVER_IP_ADDRESS, 
           SERVER_PORT_NUMBER, hello_world_message);

    // Release the allocated resources to the socket.
    close(client_socket_fd);

    return EXIT_SUCCESS; 
}
