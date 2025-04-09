#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){
    int clientsocket, port;
    struct sockaddr_in serveraddr;
    socklen_t len;
    struct hostent *server;
    char message[50];

    clientsocket=socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char *)&serveraddr, sizeof(serveraddr));
    len =sizeof(serveraddr);
    serveraddr.sin_family = AF_INET;

    printf("Enter the port: ");
    scanf("%d", &port);

    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr= INADDR_ANY;
    fgets(message, 2, stdin);
    printf("Sending message to server... \n");
    sendto(clientsocket, "HI I AM CLIENT", sizeof("HI I AM CLIENT"),0,(struct sockaddr*)&serveraddr, sizeof(serveraddr));
    printf("Message sent to client...\n");

    printf("Receiving message from server...\n");
    recvfrom(clientsocket,message, sizeof(message),0,(struct sockaddr*)&serveraddr, &len);
    printf("Server: %s",message);
    close(clientsocket);
    return 0;
}