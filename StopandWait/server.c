#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define BUFF_SIZE 1024
#define TIMEOUT 3

int main()
{
    int clientsocket, serversocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    char buffer[BUFF_SIZE]={0};
    int ack = 40;

    srand(time(0));

    serversocket=socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    printf("Enter the port: ");
    scanf("%d", &port);
 
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr= INADDR_ANY;

    
    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    printf("\nBinded\n");
    listen(serversocket,5);

    bzero((char *)&clientaddr, sizeof(clientaddr));
    len=sizeof(clientaddr);
    clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, &len);

    while(1)
    {
        memset(buffer, 0, BUFF_SIZE);

        int recv_size = recv(clientsocket, buffer, sizeof(buffer), 0);
        if(recv_size <= 0)
            break;

        if(rand()%100 < ack){
            send(clientsocket, "ACK", 3, 0);
            printf("Ack send\n");
        }
        else{
            send(clientsocket, "NAK", 3, 0);
            printf("Ack lost\n");
        }
    }
        close(serversocket);
        close(clientsocket);
        return 0;
    }

    