// Henry Ngo 
// Project 4 
// Server and client interaction using threads

#define MAX_SIZE 1000
#define MAX_LENGTH 25
#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int readcnt;
sem_t mutex, w;

int main(int argc, char *argv[]){
    int clientfd;  //file descriptor to communicate with the server
    char *host, *port;
    size_t n;
    char buffer[MAXLINE]; //MAXLINE = 8192 defined in csapp.h
    int runFlag = 1;

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	   exit(0);
    }

    host = argv[1];
    port = argv[2];
    clientfd = Open_clientfd(host, port);

    do{
        printf("(1) Add record\n");
        printf("(2) Search by Name\n");
        printf("(3) Search by Zip Code\n");
        printf("(4) Search by Salary\n");
        printf("(5) Terminate\n");
        printf("Select an option [1,2,3,4, or 5]: ");

        // Get client's option
        bzero(buffer,MAXLINE);
        Fgets(buffer,MAXLINE,stdin);  
        // removes newline character
        strtok(buffer, "\n"); 
 
        // If user selects option 1; get first name, last name, zip code, department, and salary. 
        if (strcmp(buffer, "1") == 0){  
            printf("\n");
            // Send client's option to the server 
            n = write(clientfd,buffer,strlen(buffer));

            // This allows one writer to write at a time 
            n = read(clientfd,buffer,strlen(buffer));

            // Get first name of employee and send the information to the server. 
            printf("Enter First Name: "); 
            Fgets(buffer,MAXLINE,stdin);
            strtok(buffer, "\n"); 
            n = write(clientfd,buffer,strlen(buffer));

            // Get last name of employee and send the information to the server. 
            printf("Enter Last Name: "); 
            Fgets(buffer,MAXLINE,stdin);
            strtok(buffer, "\n");
            n = write(clientfd,buffer,strlen(buffer));

            // Get zip code of employee and send the information to the server. 
            printf("Enter Zip Code: "); 
            Fgets(buffer,MAXLINE,stdin);
            strtok(buffer, "\n");
            n = write(clientfd,buffer,strlen(buffer));

            // Get department of employee and send the information to the server. 
            printf("Enter Department: "); 
            Fgets(buffer,MAXLINE,stdin);
            strtok(buffer, "\n");
            n = write(clientfd,buffer,strlen(buffer));

            // Get salary of employee and send the information to the server. 
            printf("Enter Salary: "); 
            Fgets(buffer,MAXLINE,stdin);
            strtok(buffer, "\n");
            n = write(clientfd,buffer,strlen(buffer));
            
            // Read results from server 
            printf("Message from Server: \n");
            bzero(buffer,MAXLINE);
            n = read(clientfd,buffer,MAXLINE);
            if(!n){
                perror("Read Error!!");
                return(-1);
            }
            Fputs(buffer,stdout);   
         }
        // If user selects option 2, get first name and last name 
        else if (strcmp(buffer, "2") == 0){
            printf("\n");
            
            // send the clients option to the server
            n = write(clientfd,buffer,strlen(buffer));

            n = read(clientfd,buffer,strlen(buffer));
            
            // Get first name of employee and send the information to the server. 
            printf("Enter First Name: "); 
            Fgets(buffer,MAXLINE,stdin);
            strtok(buffer, "\n"); 
            n = write(clientfd,buffer,strlen(buffer));

            // Get last name of employee and send the information to the server. 
            printf("Enter Last Name: "); 
            Fgets(buffer,MAXLINE,stdin);
            strtok(buffer, "\n");
            n = write(clientfd,buffer,strlen(buffer));

            // Read results from server 
            printf("Message from Server: \n");
            bzero(buffer,MAXLINE);
            n = read(clientfd,buffer,MAXLINE);
            if(!n){
                perror("Read Error!!");
                return(-1);
            }
            Fputs(buffer,stdout);  
         }
        // If user selects option 3, get zip code
        else if (strcmp(buffer, "3") == 0){
            printf("\n");
            // send the clients option to the server
            n = write(clientfd,buffer,strlen(buffer));

            n = read(clientfd,buffer,strlen(buffer));

            // Get zip Code of employee and send the information to the server. 
            printf("Enter Zip Code: "); 
            Fgets(buffer,MAXLINE,stdin);
            strtok(buffer, "\n");
            n = write(clientfd,buffer,strlen(buffer));
            
            // Read results from server 
            printf("Message from Server: \n");
            bzero(buffer,MAXLINE);
            n = read(clientfd,buffer,MAXLINE);
            if(!n){
                perror("Read Error!!");
                return(-1);
            }
            Fputs(buffer,stdout); 
         }
        // If user selects option 4, get salary and comparison type
        else if (strcmp(buffer, "4") == 0){
            printf("\n");
            // send the clients option to the server
            n = write(clientfd,buffer,strlen(buffer));

            n = read(clientfd,buffer,strlen(buffer));

            // Get salary of employee and send the information to the server. 
            printf("Enter Salary: "); 
            Fgets(buffer,MAXLINE,stdin);
            strtok(buffer, "\n");
            n = write(clientfd,buffer,strlen(buffer));

            // Get comparison of salary and send the information to the server. 
            printf("Enter Comparison Type [’>’,’<’,’==’,’>=’,’<=’]: ");
            Fgets(buffer,MAXLINE,stdin);
            strtok(buffer, "\n");
            n = write(clientfd,buffer,strlen(buffer));

            // Read results from server 
            printf("Message from Server: \n");
            bzero(buffer,MAXLINE);
            n = read(clientfd,buffer,MAXLINE);
            if(!n){
                perror("Read Error!!");
                return(-1);
            }
            Fputs(buffer,stdout); 
         }
        // If user selects option 5, the client will terminate 
        else if (strcmp(buffer, "5") == 0){
            n = write(clientfd,buffer,strlen(buffer));
            bzero(buffer,MAXLINE);
            n = read(clientfd,buffer,MAXLINE);
            if(!n){
                perror("Read Error!!");
                return(-1);
            }
            
            printf("Message from Server: \n");
            Fputs(buffer,stdout); 
            runFlag = 0; 
            Close(clientfd); 
        }
        // If user selects invalid option, run the loop until valid option is selected 
        else{
            n = write(clientfd,buffer,strlen(buffer));
    
            printf("Message from Server: \n");
            n = read(clientfd,buffer,MAXLINE);
            if(!n){
                perror("Read Error!!");
                return(-1);
            }
            Fputs(buffer,stdout); 
        }
        printf("\n");
    }
    while (runFlag);
    return 0;
}
