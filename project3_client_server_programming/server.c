// Henry Ngo 
// Project 3 
// Server and client interaction

#define MAX_SIZE 1000
#define MAX_LENGTH 25
#include "csapp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char zipCode[MAX_LENGTH];
    char department[MAX_LENGTH];
    int salary;
} Struct_Employee_Info;

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
    Struct_Employee_Info employees[MAX_SIZE]; 
    char line[MAX_SIZE]; 
    int count = 0; 

    // fopen arguments: filename and mode
    file = fopen("records.csv", "r"); 
    if (file == NULL) {
        printf("Unable to open the file./n");
        return; 
    }
    
    // Fgets arguments: string array, legnth, file object
    // Read information from file into employees struct
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,], %[^,], %[^,], %[^,], %d", employees[count].firstName, employees[count].lastName, employees[count].zipCode, employees[count].department, &employees[count].salary);
        count++;
    }
    fclose(file);
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
           
        }
        //Option 2 
        else if (strcmp(buffer,"2") == 0){
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
        }
        //Option 3 
        else if (strcmp(buffer,"3") == 0){
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
        }
        //Option 4 
        else if (strcmp(buffer,"4") == 0){
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
    while (1) {
    	clientlen = sizeof(struct sockaddr_storage);

        // wait for the connection from the client.
    	connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname,
                                   MAXLINE,client_port, MAXLINE, 0);

        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        serverFunction(connfd);
    
        Close(connfd);
        printf("(%s, %s) disconnected\n", client_hostname, client_port);
    }
    exit(0);
}