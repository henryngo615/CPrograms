// Henry Ngo 
// Project 4 
// Server and client interaction using threads

#define MAX_SIZE 1000
#define MAX_LENGTH 25
#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char zipCode[MAX_LENGTH];
    char department[MAX_LENGTH];
    int salary;
} Struct_Employee_Info;

// Each thread has a unique port and its own connfd value
typedef struct {
    int connfd; 
    char client_hostname[MAXLINE]; 
    char client_port[MAXLINE]; 
} Struct_Client_Info;

int readcnt = 0;
sem_t mutex, w;
Struct_Employee_Info employees[MAX_SIZE];
int count = 0;

void *my_thread_one(void *arg); 

void serverFunction(int connfd); 

char* searchByName(Struct_Employee_Info employees[], int count, const char *firstName, const char *lastName); 

char* searchByZipCode(Struct_Employee_Info employees[], int count, const char *zipCode); 

char* searchBySalary(Struct_Employee_Info employees[], int count, int salary, const char *comparisonOperator); 

    
int main(int argc, char *argv[]){
    int listenfd;
    //file descriptor to communicate with the client
    int connfd; 
    socklen_t clientlen;
    struct sockaddr_storage clientaddr; 
    
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc != 2) {
    	fprintf(stderr, "usage: %s <port>\n", argv[0]);
    	exit(0);
    }

    //wrapper function that calls getadderinfo, socket, bind, and listen functions in the server side
    listenfd = Open_listenfd(argv[1]); 

    //Server runs in the infinite loop until it is manual terminated by pressing CTRL + c

    FILE* file; 
    char line[MAX_SIZE]; 


    // fopen arguments: filename and mode
    file = fopen("records.csv", "r"); 
    if (file == NULL) {
        printf("Unable to open the file./n");
    }
    
    // Fgets arguments: string array, legnth, file object
    // Read information from file into employees struct
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,], %[^,], %[^,], %[^,], %d", employees[count].firstName, employees[count].lastName, employees[count].zipCode, employees[count].department, &employees[count].salary);
        count++;
    }
    fclose(file);
    
    Sem_init(&mutex, 0, 1);
    Sem_init(&w, 0, 1);
    pthread_t threadOne;
    
    while (1) {
    	clientlen = sizeof(struct sockaddr_storage);

        // wait for the connection from the client.
    	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE,client_port, MAXLINE, 0);
        
        Struct_Client_Info *clientInfo = malloc(sizeof(Struct_Client_Info)); 
        
        clientInfo->connfd = connfd; 
        strcpy(clientInfo->client_hostname, client_hostname); 
        strcpy(clientInfo->client_port, client_port);

        // Create new thread when client joins and sends in client connfd, hostname and port number
        pthread_create(&threadOne, NULL, my_thread_one, clientInfo);
    }
    exit(0);
}

void *my_thread_one(void *arg){
    Pthread_detach(pthread_self());
    Struct_Client_Info *clientInfo = arg; 
    
    printf("Connected to (%s, %s)\n", clientInfo->client_hostname, clientInfo->client_port);
    serverFunction(clientInfo->connfd);
    Close(clientInfo->connfd);
    printf("(%s, %s) disconnected\n", clientInfo->client_hostname, clientInfo->client_port);
    Free(arg);
    return NULL;
}

void serverFunction(int connfd){
    char buffer[MAXLINE]; 
    char firstName[MAX_LENGTH]; 
    char lastName[MAX_LENGTH]; 
    char zipCode[MAX_LENGTH];
    char department[MAX_LENGTH];
    char comparsion[MAX_LENGTH]; 
    int salary; 
    size_t n;
    FILE* file; 
    
    int run = 1; 
    while (run){
        // Read the option from client
        bzero(buffer,MAXLINE);
        n = read(connfd, buffer, MAXLINE);
        
        if(!n){
            printf("Read Error!!\n");
            return;
        }
        
        //Option 1 
        if (strcmp(buffer,"1") == 0){ 
            P(&w);
            n = write(connfd,buffer,strlen(buffer));
            file = fopen("records.csv", "a+"); 
            if (file == NULL) {
                printf("Unable to open the file./n");
                return; 
            }
            // Read the first name
            bzero(buffer,MAXLINE);
            n = read(connfd, buffer, MAXLINE);
            if(!n){
                printf("Read Error!!\n");
                return;
            }
            strcpy(firstName, buffer);

            // Read last name
            bzero(buffer,MAXLINE);
            n = read(connfd, buffer, MAXLINE);
            if(!n){
                printf("Read Error!!\n");
                return;
            }
            strcpy(lastName, buffer);

            // Read zip code
            bzero(buffer,MAXLINE);
            n = read(connfd, buffer, MAXLINE);
            if(!n){
                printf("Read Error!!\n");
                return;
            }
            strcpy(zipCode, buffer);

            // Read department
            bzero(buffer,MAXLINE);
            n = read(connfd, buffer, MAXLINE);
            if(!n){
                printf("Read Error!!\n");
                return;
            }
            strcpy(department, buffer);

            // Read salary
            bzero(buffer,MAXLINE);
            n = read(connfd, buffer, MAXLINE);
            if(!n){
                printf("Read Error!!\n");
                return;
            }
            salary = atoi(buffer);

            // writes to the file when given employee information
            fprintf(file, "\n%s,%s,%s,%s,%d", firstName, lastName, zipCode, department, salary);  
            strcpy(employees[count].firstName, firstName); 
            strcpy(employees[count].lastName, lastName);
            strcpy(employees[count].zipCode, zipCode);
            strcpy(employees[count].department, department);
            employees[count].salary = salary; 
            count++;
   
            n= write(connfd,"Record added Sucessfully!!\n",strlen("Record added Sucessfully!!\n"));
          
            fclose(file);
            V(&w);
        }
        //Option 2 
        else if (strcmp(buffer,"2") == 0){
            P(&mutex);
            readcnt++;
            if (readcnt == 1) /* First in */
                P(&w);
            V(&mutex);
            n = write(connfd,buffer,strlen(buffer));
            // Read the first name
            bzero(buffer,MAXLINE);
            n = read(connfd, buffer, MAXLINE);
            if(!n){
                printf("Read Error!!\n");
                return;
            }
            strcpy(firstName, buffer);

            // Read last name
            bzero(buffer,MAXLINE);
            n = read(connfd, buffer, MAXLINE);
            if(!n){
                printf("Read Error!!\n");
                return;
            }
            strcpy(lastName, buffer);

            // Call SearchByName function 
            char *result = searchByName(employees, count, firstName, lastName);

            // if result is empty then no record was found
            if (strlen(result) == 0){
                n= write(connfd,"No record found!!\n",strlen("No record found!!\n"));      
            }
            else{
                n= write(connfd,result,strlen(result));    
            }
            P(&mutex);
            readcnt--;
            if (readcnt == 0) /* Last out */
                V(&w);
            V(&mutex);
        }
        //Option 3 
        else if (strcmp(buffer,"3") == 0){
            P(&mutex);
            readcnt++;
            if (readcnt == 1) /* First in */
                P(&w);
            V(&mutex);
            n = write(connfd,buffer,strlen(buffer));
            
            // Read zip code
            bzero(buffer,MAXLINE);
            n = read(connfd, buffer, MAXLINE);
            if(!n){
                printf("Read Error!!\n");
                return;
            }
            strcpy(zipCode, buffer);
            char *result = searchByZipCode(employees, count, zipCode);
            
            // if result is empty then no record was found
            if (strlen(result) == 0){
                n= write(connfd,"No record found!!\n",strlen("No record found!!\n"));
            }
            else{
                n= write(connfd,result,strlen(result)); 
            }
            P(&mutex);
            readcnt--;
            if (readcnt == 0) /* Last out */
                V(&w);
            V(&mutex);
        }
        //Option 4 
        else if (strcmp(buffer,"4") == 0){
            P(&mutex);
            readcnt++;
            if (readcnt == 1) /* First in */
                P(&w);
            V(&mutex);
            n = write(connfd,buffer,strlen(buffer));
            
            // Read salary
            bzero(buffer,MAXLINE);
            n = read(connfd, buffer, MAXLINE);
            if(!n){
                printf("Read Error!!\n");
                return;
            }
            salary = atoi(buffer);

            // Read comparison
            bzero(buffer,MAXLINE);
            n = read(connfd, buffer, MAXLINE);
            if(!n){
                printf("Read Error!!\n");
                return;
            }
            strcpy(comparsion, buffer);
            char *result = searchBySalary(employees, count, salary, comparsion);

            // if result is empty then no record was found
            if (strlen(result) == 0){
                n= write(connfd,"No record found!!\n",strlen("No record found!!\n"));
            }
            else{
                n= write(connfd,result,strlen(result));
            }
            P(&mutex);
            readcnt--;
            if (readcnt == 0) /* Last out */
                V(&w);
            V(&mutex);
        }
        //Option 5 
        else if (strcmp(buffer,"5") == 0){
            n= write(connfd,"Connection Closed!!\n",strlen("Connection Closed!!\n"));
            run = 0;
            bzero(buffer,MAXLINE);
        }
        // If the selected option is not valid, the client should select a valid option again
        else{
            n= write(connfd,"Enter a valid option.\n",strlen("Enter a valid option.\n"));
            bzero(buffer,MAXLINE);
        }  
        
    }
    return;
}

// Parameters: employee struct, number of employees, first name, last name
// Search for an employee in an array of structs 
char* searchByName(Struct_Employee_Info employees[], int count, const char *firstName, const char *lastName) {
    char *result = malloc(MAX_SIZE * sizeof(char));
    char *result1 = malloc(MAX_SIZE * sizeof(char));
    bzero(result,MAX_SIZE);

    // strcmp takes 2 arugments and returns 0 if the expression is equal to each other
    // sprintf arugments (char pointer, format, variables...)
    // strcat will concatenate the char pointers and takes two arugments (destination, source)
    for (int i = 0; i < count; i++){
        if ((strcmp(employees[i].firstName, firstName) == 0) && (strcmp(employees[i].lastName, lastName) == 0)) {
            sprintf(result1, "%s,%s,%s,%s,%d\n", employees[i].firstName, employees[i].lastName, employees[i].zipCode, employees[i].department, employees[i].salary); 
            strcat(result, result1);        
        }
    }
    return result;
}

// Parameters: employee struct, number of employees, zip code
// Search for an employee in an array of structs when given a zip code
char* searchByZipCode(Struct_Employee_Info employees[], int count, const char *zipCode) {
    char *result = malloc(MAX_SIZE * sizeof(char));
    char *result1 = malloc(MAX_SIZE * sizeof(char));

    bzero(result,MAX_SIZE);    

    // strcmp takes 2 arugments and returns 0 if the expression is equal to each other
    // sprintf arugments (char pointer, format, variables...)
    // strcat will concatenate the char pointers and takes two arugments (destination, source)
    for (int i = 0; i < count; i++){
        if (strcmp(employees[i].zipCode, zipCode) == 0) {
            sprintf(result1, "%s,%s,%s,%s,%d\n", employees[i].firstName, employees[i].lastName, employees[i].zipCode, employees[i].department, employees[i].salary); 
            strcat(result, result1);
        }
    } 
    return result;
}

// Parameters: employee struct, number of employees, salary, comparison type
// Search for an employee in an array of structs when given a salary and comparison type
char* searchBySalary(Struct_Employee_Info employees[], int count, int salary, const char *comparisonOperator) {
    
    char *result1 = malloc(MAX_SIZE * sizeof(char));
    char *result = malloc(MAX_SIZE * sizeof(char));

    bzero(result,MAX_SIZE);

    // strcmp compares if comparison operator is equal to ">= "
    // iterates through salary of each struct in arr with passed in value
    // if struct salary >= salary; copy struct into result1 and append to result
    // A flag is used to determine whether employee matches with given arugments
    if (strcmp(comparisonOperator, ">=") == 0) {
        for (int i = 0; i < count; i++){
            if(employees[i].salary >= salary){
                sprintf(result1, "%s,%s,%s,%s,%d\n", employees[i].firstName, employees[i].lastName, employees[i].zipCode, employees[i].department, employees[i].salary); 
                strcat(result, result1); 
            }
        } 
    }
    
    // strcmp compares if comparison operator is equal to "<="   
    if (strcmp(comparisonOperator, "<=") == 0) {
        for (int i = 0; i < count; i++){
            if(employees[i].salary <= salary){
                sprintf(result1, "%s,%s,%s,%s,%d\n", employees[i].firstName, employees[i].lastName, employees[i].zipCode, employees[i].department, employees[i].salary); 
                strcat(result, result1); 
            }
        } 
    }

    // strcmp compares if comparison operator is equal to "=="
    if (strcmp(comparisonOperator, "==") == 0) {
        for (int i = 0; i < count; i++){
            if(employees[i].salary == salary){
                sprintf(result1, "%s,%s,%s,%s,%d\n", employees[i].firstName, employees[i].lastName, employees[i].zipCode, employees[i].department, employees[i].salary); 
                strcat(result, result1); 
            }
        }    
    }

    // strcmp compares if comparison operator is equal to ">"
    if (strcmp(comparisonOperator, ">") == 0) {
        for (int i = 0; i < count; i++){
            if(employees[i].salary > salary){
                sprintf(result1, "%s,%s,%s,%s,%d\n", employees[i].firstName, employees[i].lastName, employees[i].zipCode, employees[i].department, employees[i].salary); 
                strcat(result, result1); 
            }
        }   
    }

    // strcmp compares if comparison operator is equal to "< "
    if (strcmp(comparisonOperator, "<") == 0) {
        for (int i = 0; i < count; i++){
            if(employees[i].salary < salary){
                sprintf(result1, "%s,%s,%s,%s,%d\n", employees[i].firstName, employees[i].lastName, employees[i].zipCode, employees[i].department, employees[i].salary); 
                strcat(result, result1);   
            } 
        }
    }
    return result;
}