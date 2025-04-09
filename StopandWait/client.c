#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define BUFF_SIZE 1024
#define TIMEOUT 3

int main()
{
    int clientsocket, port, recvsize;
    struct sockaddr_in serveraddr;
    char packet[50], buffer[BUFF_SIZE]={0};
    struct timeval tv = {TIMEOUT,0};

    clientsocket=socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    printf("Enter the port: ");
    scanf("%d", &port);
 
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr= INADDR_ANY;

    connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    setsockopt(clientsocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));
    printf("\nConnected");

    int i=1;

    while(1)
    {
        memset(buffer, 0, BUFF_SIZE);

        if(i>5)
        break;

        sprintf(packet, "%d", i);
        printf("\nSending packet: %d\n", i);
        send(clientsocket, packet, sizeof(packet), 0);

        recvsize = recv(clientsocket, buffer, sizeof(buffer), 0);

        if(recvsize > 0 && (strcmp(buffer, "ACK")) == 0){
            printf("Packet Sent\n");
            i++;
        }
        else{
            printf("Packet Lost\n");
        }
    }
    printf("All packets Sent\n");
    close(clientsocket);
    return 0;

}