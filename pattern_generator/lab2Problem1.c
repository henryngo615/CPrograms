// Henry Ngo 
// Lab 2 Problem 1 
// This program will use print out a number pattern using loops. 

#include <stdio.h> 
#include <stdlib.h>

int main(int argc, char *argv[]){
    //checks if there is 2 arugments: executable and single arugment
    if(argc != 2){
        printf("Provide one arugment\n");
        return 1;
    }

    //atoi function converts character string into integer value
    int n = atoi(argv[1]);

    //checks if 1 <= n <= 20 
    if((n < 1) || (n > 20)){
        printf("The value should be between 1 and 20 inclusively.\n");
        return 1;
    }
    
    for(int i = 0; i < (2 * n - 1); i++){
        for(int j = 0; j < (2 * n - 1); j++){
            int number;
            if (i < j) {
                number = i;
            } else {
                number = j;
            }

            if(number > (2 * n - 1 - i - 1)){
                number = 2 * n - 1 - i - 1;
            }

            if(number > (2 * n - 1 - j - 1)){
                number = 2 * n - 1 - j - 1;
            }

            printf("%d ", (n - number));
        }
        printf("\n");
    }
    return 0;
}
