#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    time_t currentTime;
    struct tm* timeInfo;
    
    // Create the server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }
    
    // Prepare the server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    
    // Bind the server socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding server socket");
        exit(EXIT_FAILURE);
    }
    
    // Listen for incoming connections
    if (listen(serverSocket, 1) == -1) {
        perror("Error listening for connections");
        exit(EXIT_FAILURE);
    }
    
    printf("Server listening on port %d\n", PORT);
    
    while (1) {
        socklen_t clientAddrLen = sizeof(clientAddr);
        
        // Accept a client connection
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            perror("Error accepting client connection");
            exit(EXIT_FAILURE);
        }
        
        // Get the current date and time
        currentTime = time(NULL);
        timeInfo = localtime(&currentTime);
        snprintf(buffer, BUFFER_SIZE, "%s", asctime(timeInfo));
        
        // Send the date and time to the client
        send(clientSocket, buffer, strlen(buffer), 0);
        
        // Close the client socket
        close(clientSocket);
    }
    
    // Close the server socket
    close(serverSocket);
    
    return 0;
}

