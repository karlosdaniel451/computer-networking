# Sockets

The internet and computer networks in general allow processes running on different hosts to communicate by message passing.

Any message sent from one process to another must go through the underlying network.
A process sends message into, and receives from, the network through a software interface called a **socket**.

A socket is the interface between the application layer and the transport layer within a host It is also referred to as the **Application Programming Interface (API)** between the application and the network, since the socket is the programming interface with which network applications are buit.

In order for a process running on one host to send messages to a process running on another host, the receiving process needs to identify the receiving process. This identification is made up by two pieces of information: the **IP address** of the receiving host and the **port number** which identifies the receiving host on the given host.

So in short, the socket is the interface between the application processes and the transport-layer protocol. A sending process pushes application-layer messages (such as an HTTP request message) through its socket and the transport-layer protocol has the responsibility of getting (deliverying) the messages to the socket of the receiving process.

In the Internet, the **User Datagram Protocol (UDP)** and the **Transmission Control Protocol (TCP)** are the basic transport-layer protocols provided by the Internet.

## TCP sockets

The TCP provides a **connection-oriented** service, a **reliable data transfer** service and **congestion-control** mechanism.

As the TCP is a connection-oriented protocol, before the client and server processes can start to send messages to each other, they first need to handshake and establish a TCP connection. After creating its socket, the client initiates a three-way handshake and establishes a TCP connection with the server. This mechamism is completely invisible to both client and server processes since it takes place within the transport layer. The mechanism of ensuring that the message will be correctly delivered to the socket of the receiving process is also invisible to the application.

### Using TCP sockets

A process uses a socket through **System Calls** to the Operating System Kernel, or indirectly through System Call Wrappers provided by a library such as glibc. 

// TODO

#### UDP Sockets

// TODO
