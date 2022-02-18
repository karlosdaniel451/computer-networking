package udpserver;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class App {
    public static DatagramSocket serverUDPSocket;
    public static int portNumber;

    public static InetAddress clientIPAddress;
    public static int clientPortNumber;

    public static String messageReceived;
    public static String messageToBeSent;
    public static int BUFFER_SIZE = 1024;
    public static byte[] dataReceived = new byte[BUFFER_SIZE];
    public static byte[] dataToBeSent;
    public static DatagramPacket packetReceived;
    public static DatagramPacket packetToBeSent;

    public static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        System.out.print("Enter the port number to be bound to the server socket: ");
        portNumber = scanner.nextInt();

        try {
            // Create a socket for exchanging datagrams.
            serverUDPSocket = new DatagramSocket(portNumber);
            System.out.printf(
                "\nWaiting for messages on the socket of port number %d...\n", portNumber);

            while (true) {
                packetReceived = new DatagramPacket(dataReceived, dataReceived.length);

                // Block process execution until a packet is received.
                serverUDPSocket.receive(packetReceived);

                messageReceived = new String(packetReceived.getData());

                // Get the address of the process client that sent the packet.
                clientIPAddress = packetReceived.getAddress();
                clientPortNumber = packetReceived.getPort();

                System.out.printf("\nMessage received from %s:%d: %s\n", clientIPAddress,
                    clientPortNumber, messageReceived);

                messageToBeSent = messageReceived.toUpperCase();

                dataToBeSent = messageToBeSent.getBytes();

                packetToBeSent = new DatagramPacket(
                    dataToBeSent, dataToBeSent.length, clientIPAddress, clientPortNumber);

                // Sent the capitalized sentence to process client.
                serverUDPSocket.send(packetToBeSent);
            }
        } catch (IOException ioException) {
            System.err.print(ioException);
        }
    }
}
