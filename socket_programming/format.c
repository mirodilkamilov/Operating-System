#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
    int sockfd, optval, backlog, new_socket, nbytesRead;
    char buffer[1024] = {0}, schat[1024];
    char *hello = "Hello from server";
    char *bye = "bye";
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    printf("Creating server socket");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == 0)
    {
        perror("Socket creation is failed");
        exit(EXIT_FAILURE);
    }

    printf("Defing server socket options\n");
    optval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval) < 0)
    {
        printf("Error in setsockopt function");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);       //Declare port 5000 to be used.
    address.sin_addr.s_addr = INADDR_ANY; //Permit any incoming IP address by declaring INADDR_ANY
    printf("Binding server socket\n");
    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        printf("Error in bind function");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080 for new connection");
    backlog = 5; //maximum of awaiting request
    if (listen(sockfd, backlog) < 0)
    {
        printf("Error in listen function");
        exit(EXIT_FAILURE);
    }

    new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if(new_socket<0){
        perror("Error in accept function");
        exit(EXIT_FAILURE);
    }
    printf("Server accepted new connection from client\n");

    //First client is supposed to send
    nbytesRead = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);

    send(new_socket, hello, strlen(hello), 0);
    printf(" Ready for Chat....\n");

    while (1)
    {
        memset(buffer, 0, sizeof(buffer)); //initialized to zeroes
        nbytesRead = read(new_socket, buffer, 1024);
        printf("%s\n", buffer);

        memset(schat, 0, sizeof(schat));
        printf("server : ");
        fgets(schat, sizeof(schat), stdin);
        send(new_socket, schat, strlen(schat), 0);
        schat[strlen(schat)] = '\0';
        
        if (strncmp(schat, bye, strlen(bye)) == 0)
            break;
    }
    return 0;
}