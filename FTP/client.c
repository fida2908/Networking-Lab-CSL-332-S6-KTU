#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 60              // Define maximum buffer size

int main(int argc, char *argv[]) {
    int sockfd, n,SERV_TCP_PORT;
    struct sockaddr_in serv_addr;
    char send[MAX], recvline[MAX];

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    printf("Enter the port");
    scanf("%d", &SERV_TCP_PORT);
    // Define server address structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Connect to localhost
    serv_addr.sin_port = htons(SERV_TCP_PORT);           // Set server port

    // Connect to the server
    connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // Get the filename from the user
    printf("\nEnter the source file name: ");
    scanf("%s", send);

    // Send the filename to the server
    write(sockfd, send, MAX);

    // Read and print the file content received from the server
    while ((n = read(sockfd, recvline, MAX)) != 0) {
        printf("%s", recvline);
    }

    // Close the socket
    close(sockfd);
    
    return 0;
}