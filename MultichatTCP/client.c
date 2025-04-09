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
    char message[100], reply[100];

    clientsocket=socket(AF_INET, SOCK_STREAM, 0);
    bzero((char *)&serveraddr, sizeof(serveraddr));
    len =sizeof(serveraddr);
    serveraddr.sin_family = AF_INET;

    printf("Enter the port: ");
    scanf("%d", &port);
    getchar();
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr= INADDR_ANY;

    connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    printf("\nConnected");
    while(1){
        printf("\nClient: ");
        bzero(message, sizeof(message));
        fgets(message,sizeof(message),stdin);
        send(clientsocket, message, strlen(message), 0);

        if(strncmp(message,"bye",3)==0){
            printf("Chat ended by client\n");
            break;
        }

        bzero(reply, sizeof(reply));
        recv(clientsocket, reply, sizeof(reply), 0);
        printf("Server: %s",reply);

        if(strncmp(reply,"bye",3)==0){
            printf("Chat ended by server\n");
            break;
        }
        
    }
    close(clientsocket);
    return 0;

}