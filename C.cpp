#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GENERATOR_POLYNOMIAL 0x04C11DB7

unsigned int crc_remainder(unsigned char message[], int message_size) {
    unsigned int crc = 0xFFFFFFFF;  // Initial CRC value

    for (int i = 0; i < message_size; i++) {
        crc ^= (message[i] << 24);  // XOR the next byte of the message with the MSB of the CRC

        for (int j = 0; j < 8; j++) {
            if (crc & 0x80000000) {  // If MSB of CRC is 1
                crc = (crc << 1) ^ GENERATOR_POLYNOMIAL;  // Perform a bitwise left shift and XOR with generator polynomial
            } else {
                crc <<= 1;  // Perform a bitwise left shift
            }
        }
    }

    return crc;
}

int main() {
    unsigned char message[100];
    unsigned int crc;

    printf("Enter the message: ");
    scanf("%s", message);

    int message_size = strlen((char*)message);

    // Append 4 bytes (32 bits) of zeroes as the CRC remainder
    for (int i = 0; i < 4; i++) {
        message[message_size + i] = 0x00;
    }

    crc = crc_remainder(message, message_size + 4);

    // Update the last 4 bytes of the message with the CRC remainder
    for (int i = 0; i < 4; i++) {
        message[message_size + i] = (crc >> (24 - (i * 8))) & 0xFF;
    }

    printf("Message with CRC: %s\n", message);

    // Simulate an error by changing one bit in the message
    message[3] ^= 0x01;

    // Check if the received message has any errors
    crc = crc_remainder(message, message_size + 4);

    if (crc == 0) {
        printf("Received message is error-free\n");
    } else {
        printf("Received message has errors\n");
    }

    return 0;
}

