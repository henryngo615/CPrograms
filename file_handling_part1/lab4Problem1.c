// Henry Ngo 
// Lab 4 Problem 1
// This lab will read from a file and print it out 

#include <stdio.h>
#include <ctype.h>

const int MAX_CHAR = 11; 

int main(int argc, char *argv[]){

    char arr[MAX_CHAR]; 
    
    //checks if there is 2 arugments: executable and single arugment
    if(argc != 2){
        printf("Provide one arugment\n");
        return 1;
    }

    // similar to ifstream infile
    FILE *fp; 
    // takes in file name from commandline 
    char *filename = argv[1]; 
    char ch; 
    int count = 0;
    // similar to infile.open("filename")
    fp = fopen(filename, "r");

    // checks if file is good
    if (fp == NULL){
        printf("%s Does not exist\n", filename);
    }

    // reads the characters individually until end of file 
    while ((ch = fgetc(fp)) != EOF){
        // append each character to array
        arr[count] = ch; 
        // checks if character is printable, if not, it will prints a dot 
        if(!isprint(ch)){
            arr[count] = '.';
        }
        count++;
        // when array is full, null char is added to the last element of array
        if (count == 10){
            arr[MAX_CHAR-1] = '\0';
            // prints until it reaches null character
            printf("%s", arr); 
            printf("\n");
            count = 0;
        }      
    }
    // EOF is reached before array is filled and loop is terminated, so this will print the remaining characters
    if (count != 0){
        arr[count] = '\0';
        printf("%s", arr);
        printf("\n");
    }

    // similar to infile.close()
    fclose(fp); 

    
}
    



