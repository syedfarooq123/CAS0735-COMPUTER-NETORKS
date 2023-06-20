#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesSent;

    // Create the client socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating client socket");
        exit(EXIT_FAILURE);
    }

    // Prepare the server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to the server");
        exit(EXIT_FAILURE);
    }

    // Read input from the user and send it to the server
    printf("Enter a message to send to the server (max %d characters):\n", BUFFER_SIZE - 1);
    fgets(buffer, BUFFER_SIZE, stdin);

    // Send the message to the server
    bytesSent = send(clientSocket, buffer, strlen(buffer), 0);
    if (bytesSent == -1) {
        perror("Error sending data to server");
        exit(EXIT_FAILURE);
    }

    // Receive the echoed message from the server
    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead == -1) {
        perror("Error receiving data from server");
        exit(EXIT_FAILURE);
    }

    printf("Server echoed message: %s\n", buffer);

    // Close the client socket
    close(clientSocket);

    return 0;
}

