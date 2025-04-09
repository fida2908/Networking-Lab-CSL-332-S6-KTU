#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define MAX 60              // Maximum buffer size

// Global variables
char buff[4096];  
FILE *f1;

int main(int argc, char *argv[]) {
    int sockfd, newsockfd, clength, SERV_TCP_PORT;
    struct sockaddr_in serv_addr, cli_addr;
    char t[MAX], str[MAX];

    strcpy(t, "exit");  // Initialize exit command

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    printf("Enter the port");
    scanf("%d", &SERV_TCP_PORT);
    // Configure server address structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERV_TCP_PORT);

    // Bind socket to the specified IP and port
    printf("\nBinding socket...");
    bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // Start listening for incoming connections
    printf("\nListening for connections...");
    listen(sockfd, 5);

    // Accept connection from client
    clength = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clength);

    // Close the listening socket (only needed for one connection)
    close(sockfd);

    // Read file name from client
    read(newsockfd, str, MAX);
    printf("\nClient requested file: %s\n", str);

    // Open the requested file
    f1 = fopen(str, "r");
    if (f1 == NULL) {
        printf("Error: File not found.\n");
        write(newsockfd, "ERROR: File not found", 22);
    } else {
        // Read file content and send it to the client
        while (fgets(buff, sizeof(buff), f1) != NULL) {
            write(newsockfd, buff, MAX);
        }
        fclose(f1);
        printf("\nFile transferred successfully.\n");
    }

    // Close the client connection
    close(newsockfd);
    return 0;
}