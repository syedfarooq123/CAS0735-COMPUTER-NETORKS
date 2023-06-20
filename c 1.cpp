#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

int main() {
    const char* dnsServer = "8.8.8.8";  // DNS server IP address
    const char* hostname = "www.example.com";  // Hostname to resolve

    struct addrinfo hints, *result;
    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    // Get address information for the hostname
    status = getaddrinfo(hostname, NULL, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in* address = (struct sockaddr_in*)result->ai_addr;
    char ipAddr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(address->sin_addr), ipAddr, INET_ADDRSTRLEN);

    printf("Resolved IP address: %s\n", ipAddr);

    freeaddrinfo(result);

    return 0;
}

