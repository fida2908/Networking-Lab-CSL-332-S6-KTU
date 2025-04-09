#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){
    int serversocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    struct hostent *server;
    char message[50];

    serversocket=socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    printf("Enter the port: ");
    scanf("%d", &port);

    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr= INADDR_ANY;
    bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    printf("Binded\n");

    bzero((char *)&clientaddr, sizeof(clientaddr));
    len=sizeof(clientaddr);

    printf("Receiving message from client...\n");
    recvfrom(serversocket,message, sizeof(message),0,(struct sockaddr*)&clientaddr, &len);
    printf("Client: %s",message);

    printf("\nSending message to client... \n");
    sendto(serversocket, "HI", sizeof("HI"),0,(struct sockaddr*)&clientaddr, sizeof(clientaddr));
    printf("Message sent to client.\n");

    close(serversocket);
    return 0;
}