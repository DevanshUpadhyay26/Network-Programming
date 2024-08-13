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



    int num1, num2, ans, choice;





 S: n=write(newsockfd, "Enter Number 1: ",strlen("Enter Number 1: ")); // Req for Number 1
    if(n<0){
        error("Error while Write Operation in socket!!");
    }
    read(newsockfd, &num1, sizeof(int));        // Read Number 1
    printf("Client - Number 1 is: %d\n", num1);



   n=write(newsockfd, "Enter Number 2: ",strlen("Enter Number 2: ")); // Req for Number 2
    if(n<0){
        error("Error while Write Operation in socket!!");
    }
    read(newsockfd, &num2, sizeof(int));        // Read Number 2
    printf("Client - Number 2 is: %d\n", num2);


    n=write(newsockfd,"Enter Your Choice:\n 1. Add\n 2. Sub\n 3. Multiply\n 4. Divide\n 5. Mod\n 6.Exit\n",strlen("Enter Your Choice :\n 1. Add\n 2. Sub\n 3. Multiply\n 4. Divide\n 5. Mod\n 6.Exit\n"));      // Asking for Choice

    if(n<0){
        error("Oops, something came up in selection!");
    }
    read(newsockfd, &choice, sizeof(int));          //Read choice
    printf("Client - Choice is : %d\n", choice);

        switch (choice)
        {
        case 1:
            ans=num1+num2;
            break;
        case 2:
            ans=num1-num2;
            break;
        case 3:
            ans=num1*num2;
            break;
        case 4:
            ans=num1/num2;
            break;
        case 5:
            ans=num1%num2;
            break;
        case 6:
            goto Q;
            break;
        default:
            break;
        }


    write(newsockfd, &ans, sizeof(int));
    if(choice != 6){
        goto S;
    }
Q:    close(newsockfd);
    close(sockfd);
    return 0;
}