#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define NUM_REQUESTS 10000

int main() {
    // Set the IP address to stress test
    char *ip_address = "127.0.0.1";

    // Set the port to use
    int port = 80;

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
        return 1;
    }

    // Set the IP address and port of the server to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(ip_address);

    // Connect to the server
    if (connect(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Error connecting to server");
        return 1;
    }

    // Send NUM_REQUESTS requests to the server
    for (int i = 0; i < NUM_REQUESTS; i++) {
        char request[] = "GET / HTTP/1.1\r\n\r\n";
        if (send(sock, request, sizeof(request), 0) < 0) {
            perror("Error sending request");
            return 1;
        }
    }

    // Close the socket
    close(sock);

    return 0;
}
