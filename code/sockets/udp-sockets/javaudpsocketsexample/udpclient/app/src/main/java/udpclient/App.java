package udpclient;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;

public class App {
    public static DatagramSocket clientUDPSocket;

    public static InetAddress serverIPAddress;
    public static int serverPortNumber;

    public static String messageReceived;
    public static byte[] dataReceived;
    public static DatagramPacket packetReceived;
    public static final int BUFFER_SIZE = 1024;

    public static String messageToBeSent;
    public static byte[] dataToBeSent;
    public static DatagramPacket packetToBeSent;

    public static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        try {
            // Create a socket for exchanging datagrams.
            clientUDPSocket = new DatagramSocket();

            System.out.print("Enter the server hostname/IP address: ");
            serverIPAddress = InetAddress.getByName(scanner.nextLine());

            System.out.print("Enter the server socket port number: ");
            serverPortNumber = scanner.nextInt();

            scanner.nextLine(); // Create Scanner buffer.

            System.out.printf("Enter the message to be sent to server process at %s:%d: ",
                serverIPAddress, serverPortNumber);
            messageToBeSent = scanner.nextLine();

            dataToBeSent = messageToBeSent.getBytes();

            packetToBeSent = new DatagramPacket(
                dataToBeSent, dataToBeSent.length, serverIPAddress, serverPortNumber);

            // Send the the datagram to the server process.
            clientUDPSocket.send(packetToBeSent);
            System.out.println("Message sent to server (there is no guarantee that it will "
                + "receive it correctly, nor that it will receive it at all).");

            dataReceived = new byte[BUFFER_SIZE];
            packetReceived = new DatagramPacket(dataReceived, dataReceived.length);

            // Block process execution until a packet is received.
            clientUDPSocket.receive(packetReceived);

            messageReceived = new String(dataReceived);

            System.out.printf("\nMessage received from server process at %s:%d: %s",
                serverIPAddress, serverPortNumber, messageReceived);

            // Close the datagram socket.
            clientUDPSocket.close();
        } catch (IOException ioException) {
            System.err.print(ioException);
        }
    }
}
