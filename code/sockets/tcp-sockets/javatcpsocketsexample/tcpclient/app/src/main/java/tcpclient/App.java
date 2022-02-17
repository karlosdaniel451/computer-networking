package tcpclient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.Scanner;

public class App {
    public static String serverSocketIPAddress;
    public static int serverSocketPortNumber;
    public static Socket serverSocket;

    public static String messageReceived;

    public static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        System.out.print("Enter the server hostname/IP address: ");
        serverSocketIPAddress = scanner.nextLine();

        System.out.print("Enter the server socket port number: ");
        serverSocketPortNumber = scanner.nextInt();

        try {
            // Create a socket and establish a TCP connection with the server process.
            serverSocket = new Socket(serverSocketIPAddress, serverSocketPortNumber);
            System.out.println("\nTCP connection established.");

            InputStream serverInputStream = serverSocket.getInputStream();
            BufferedReader serverBufferedReader =
                new BufferedReader(new InputStreamReader(serverInputStream));

            // Read and print the received messages from the server process.
            while ((messageReceived = serverBufferedReader.readLine()) != null) {
                System.out.printf(
                    "%s:%d: %s\n", serverSocketIPAddress, serverSocketPortNumber, messageReceived);
            }

            // Close the TCP connection.
            serverSocket.close();
        } catch (IOException ioException) {
            System.err.print(ioException);
        }
    }
}
