#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h> 

int main() {
    int client;
    int num[10] = {0};
    struct sockaddr_in servAddr;
    socklen_t servAddr_length = sizeof(servAddr);

    client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (client < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully\n");

    memset(&servAddr, 0, sizeof(servAddr)); 
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(3003);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("\nEnter number to send: ");
    int d;
    if (scanf("%d", &d) != 1) {
        fprintf(stderr, "Invalid input\n");
       
        return EXIT_FAILURE;
    }
    num[0] = d;

    if (sendto(client, num, sizeof(num), 0, (struct sockaddr*)&servAddr, servAddr_length) < 0) {
        perror("Sending error");
       
        exit(EXIT_FAILURE);
    }
    printf("\nSending....\n");

    if (recvfrom(client, num, sizeof(num), 0, (struct sockaddr*)&servAddr, &servAddr_length) < 0) {
        perror("Receiving error");
        
        exit(EXIT_FAILURE);
    }
    printf("\nFrom SERVER: %d\n", num[0]);
    printf("End...........\n");

  //  close(client);
    return 0;
}
