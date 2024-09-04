// Henry Ngo 
// Lab 2 Problem 2
// This program will use calculate the permutation and combination formula of two given integers.   

#include <stdio.h> 
#include <stdlib.h>

//Function prototype; will pass one arugment
long factorial(int num);

int main(int argc, char *argv[]){
    //checks if there is three arugments: executable and two arugments
    if(argc != 3){
        printf("Provide two arugments.\n");
        return 1;
    }
    //atoi function converts character string into integer value
    int n = atoi(argv[1]);
    int r = atoi(argv[2]);

    // long data type is needed to hold larger values
    long temp; 
    long temp1; 

    //calls factorial function to do factorial calculation and return result
    long permutation = (temp = factorial(n))/(temp1 = factorial(n-r));
    //%lu is the format specifier for long
    printf("P(%d,%d) = %lu\n", n, r, permutation); 

    //calls factorial function to do factorial calculation and return result
    long combination = (permutation)/(temp = factorial(r));
    printf("C(%d,%d) = %lu\n", n, r, combination); 
}

long factorial(int num){
    long number = 1;
    for(int i = 1; i <= num; i++){
        number = number * i;
    }
    return number;
}
