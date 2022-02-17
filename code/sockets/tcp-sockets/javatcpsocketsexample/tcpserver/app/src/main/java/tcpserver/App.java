package tcpserver;

import java.io.*;
import java.net.*;
import java.util.Date;
import java.util.Scanner;

public class App {
    public static int welcomingSocketPortNumber;
    public static ServerSocket welcomingSocket;
    public static Socket connectionSocket;

    public static String messageReceived;
    public static String messageToBeSent;

    public static String clientIPAddress;
    public static int clientPortNumber;

    public static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        System.out.print("Enter the port number to be bound to the welcoming socket: ");
        welcomingSocketPortNumber = scanner.nextInt();

        try {
            welcomingSocket = new ServerSocket(welcomingSocketPortNumber);

            // Wait for TCP connection requests from a client process.
            while (true) {
                System.out.printf(
                    "\nWaiting for TCP connection requests on the socket of port number %d...\n",
                    welcomingSocketPortNumber);

                // Accept the establishment of a TCP connection.
                connectionSocket = welcomingSocket.accept();
                messageToBeSent = new Date().toString();
                System.out.printf("\nTCP connection established with client process at %s:%d.\n",
                    connectionSocket.getInetAddress().toString(), connectionSocket.getPort());

                PrintWriter printWriter = new PrintWriter(connectionSocket.getOutputStream(), true);

                // Send the current date to client process.
                printWriter.println(messageToBeSent);
                System.out.printf("Message sent to %s:%d: %s\n",
                    connectionSocket.getInetAddress().toString(), connectionSocket.getPort(),
                    messageToBeSent);

                // Close the socket and resume listening for TCP connection requests.
                connectionSocket.close();
            }
        } catch (IOException ioException) {
            System.err.print(ioException);
        }
    }
}
