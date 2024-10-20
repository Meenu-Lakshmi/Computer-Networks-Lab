#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define PORT 3003
#define BUFFER_SIZE 1024

int main() {
    int server;
    int num[10] = {0};
    char servmsg[BUFFER_SIZE];
    struct sockaddr_in servAddr, ClientAddr;
    socklen_t client_length = sizeof(ClientAddr);

    server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully\n");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(PORT);
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(server, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0) {
        perror("Binding failed");
  
        exit(EXIT_FAILURE);
    }
    printf("Binding...\nListening on port %d...\n", PORT);

    if (recvfrom(server, num, sizeof(num), 0, (struct sockaddr*)&ClientAddr, &client_length) < 0) {
        perror("Receiving error");

        exit(EXIT_FAILURE);
    }

    printf("\nFrom CLIENT: %d\n", num[0]);

    int sum = 0;
    int m = num[0];

    for (int i = 0; m > 0; i++) {
        int n = m % 10; // last digit
        sum += n * (1 << i); 
    }
   
    num[0] = sum; 
    printf("Binary sum: %d\n", sum);

    if (sendto(server, num, sizeof(num), 0, (struct sockaddr*)&ClientAddr, client_length) < 0) {
        perror("Sending error");
      
        exit(EXIT_FAILURE);
    }
    printf("Sending response...\n");

    //close(server);
    return 0;
}
