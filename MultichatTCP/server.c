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
    int clientsocket, serversocket, port;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len;
    struct hostent *server;
    char message[100], reply[100];

    serversocket=socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;

    printf("Enter the port: ");
    scanf("%d", &port);
    getchar();
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr= INADDR_ANY;

    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    printf("\nBinded\n");
    listen(serversocket,5);

    bzero((char *)&clientaddr, sizeof(clientaddr));
    len=sizeof(clientaddr);
    clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, &len);
    while(1){

        bzero(message, sizeof(message));
        recv(clientsocket, message, sizeof(message), 0);
        printf("Client: %s",message);

        if(strncmp(message,"bye",3)==0){
            printf("Chat ended by client\n");
            break;
        }
        
        printf("Server: ");
        bzero(reply, sizeof(reply));
        
        fgets(reply,sizeof(reply),stdin);
        send(clientsocket, reply, strlen(reply), 0);

        if(strncmp(reply,"bye",3)==0){
            printf("Chat ended by server\n");
            break;
        }

    }
    close(clientsocket);
    close(serversocket);
    return 0;

}