#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define h_addr h_addr_list[0]

void error(const char *msg){
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[255];
    if(argc < 3){
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("Error Opening the Socket");
    }

    server = gethostbyname(argv[1]);
    if(server == NULL){
        fprintf(stderr, "Error, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("Connection Failed");
    }


    int num1, num2, choice, ans;


S:  bzero(buffer, 255);
    n=read(sockfd, buffer, 255);        // Read the server String 1
    if(n<0){
        error("Error while reading from socket");
    }
    printf("Server: %s\n", buffer);
    scanf("%d", &num1);
    write(sockfd, &num1, sizeof(int));          // Send no 1 to server
    

    ///////////////////////////////////////////////////
    bzero(buffer, 255);
    n=read(sockfd, buffer, 255);        // Read the server String 2
    if(n<0){
        error("Error while reading from socket");
    }
    printf("Server: %s\n", buffer);
    scanf("%d", &num2);
    write(sockfd, &num2, sizeof(int));          // Send no 2 ro server

////////////////////////////////////////////////////////////////
    bzero(buffer, 255);
    n=read(sockfd, buffer, 255);        // Read the server
    if(n<0){
        error("Error while reading from socket");
    }
    printf("Server: %s\n", buffer);
    scanf("%d", &choice);
    write(sockfd, &choice, sizeof(int));

    if(choice == 6){
        goto Q;
    }
    read(sockfd, &ans, sizeof(int));
    printf("Server: the Answer is : %d\n", ans);


    if(choice !=6){
        goto S;
    }



Q:  printf("You have selected Exit. Sayonaraa\n");
    close(sockfd);
    return 0;
}
