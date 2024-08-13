#include <stdio.h>      // IO CRUD
#include <stdlib.h>     //Macros, general functions
#include <string.h>     //String Manipulation
#include <unistd.h>     //
#include <sys/types.h>  //Definition of a number of data type used in system calls
#include <sys/socket.h> //Socket address, Sturcture of internet use
#include <netinet/in.h> // in.h  constants and structures for internet domain address

void error(const char *msg){
    perror(msg); //Standard error
    exit(1);
}

int main(int argc, char *argv[]){
    if(argc<2){
        fprintf(stderr, "PORT NUMBER NOT PROVIDED. PROGRAM TERMINATED\n");
        exit(1);
    }
    int sockfd, newsockfd, portno, n;
    char buffer[255];
    struct sockaddr_in serv_addr, cli_addr;  //sockaddr_in gives internet addr
    socklen_t clilen;   //32 bit data type of socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd<0){
        error("Error Opening Socket");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi (argv[1]);   //Int -> String
    serv_addr.sin_family=AF_INET;

    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd , (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        error("Binding Failed");
    }



    listen(sockfd , 5);
    clilen = sizeof(cli_addr);

    newsockfd = accept (sockfd, (struct sockaddr *) &cli_addr, &clilen);

    if(newsockfd<0){
        error("Error on Accepting Socket");
    }

    while(1){
        bzero(buffer, 255);
        n=read(newsockfd, buffer,255);
        if(n<0){
            error("Error on Reading the socket");
        }
        printf("Client: %s\n", buffer);
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);


        n=write(newsockfd, buffer, strlen(buffer));
        if(n<0){
            error("Error on Writing");
        }
        int i=strncmp("Connection Closed", buffer,3);
        if(i==0){
            break;
        }
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}