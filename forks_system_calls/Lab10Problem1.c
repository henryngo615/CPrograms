// Henry Ngo 
// Lab 10 Problem 1 
// Using fork system calls 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int arr[argc-1];
    int number; 
    int status;
    int total = 0; 
    float avg; 
    float totalNum = argc - 1; 
    int min = 99999; 
    int max = 0; 

    // Convert integers into another array 
    for (int i = 1; i < argc; i++){
        number = atoi(argv[i]);
        arr[i-1] = number;
    }
    
    // Fork a child process
    int pid = fork();   

    // If there is a child process then run this line 
    // Calculate average of the list of numbers
    // Need to subtract 1 from argc to account for the executable 
    if (pid == 0) {
        for (int i = 0; i < argc-1; i++){
            total +=arr[i];
        }
        avg = total/totalNum; 
        printf("The average value is %.2f\n", avg);
    }
    // Once child process is done, fork another child process
    // Calculate the minimum value in the list
    else if (pid > 0) {
        pid = fork();
        // Fork another child process
        if (pid == 0){
            for (int i = 0; i < argc-1; i++){
                 if (arr[i] < min){
                     min = arr[i];  
                }
            }
             printf("The minimum value is %d\n", min);
        }
        // The parent executes when child processes are done
        // Calculate the maximum value in the list
        else{
            for (int i = 0; i < argc-1; i++){
                 if (arr[i] > max){
                     max = arr[i];  
                 }
            } 
            waitpid(pid, &status, 0); 
            printf("The maximum value is %d\n", max);    
        }
    }
    else {
        printf("Fork Failed\n");
    }

    return 0;
}
