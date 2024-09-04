// Henry Ngo 
// Project 1: Hex Dump 
// Turn text into hexadecimal representation 

#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int MAX_CHAR = 17; 

// takes in commandline arugments 
int main(int argc, char *argv[]){
    char str[MAX_CHAR]; 
    char *filename = argv[1];
    FILE *fp; 
    char ch;
    fp = fopen(filename, "r"); 
    int count = 0; 
    int hexacounter = 0;
    int space = 0;

    // checks if there is two commandline arugments
    if(argc != 2){
        printf("Provide one arugment!\n");
        return 1;
    }

    // if file doesn't exist then it end the program
    if(fp == NULL){
        printf("%s does not exist!\n", filename);
        return 1; 
    }

    // reads characters from file until last character is reached
    while((ch = fgetc(fp)) != EOF){
        if (count == 0){
            printf("%08x: ", hexacounter);
            hexacounter+=16;
        }

        if (space == 2){
            printf(" "); 
            space = 0;
        }
        space++;
        // %x format specifier prints character ascii value as hexademcial 
        printf("%02x", ch); 

        // if it is a printable character then append to array, otherwise, append a dot. 
        if (isprint(ch)){
            str[count] = ch;
        }
        else{
            str[count] = '.';
        }    
        
        count++;
        
        // prints out the first 16 characters of array
        if (count == 16){
            str[count] = '\0';
            printf("  "); 
            printf("%s\n", str);
            space = 0;
            count = 0;
        }   
        
    }
    // print out the remaining array since while loop terminated early 
    if (count != 0){
        str[count] = '\0';
        
        for(int i = 0; i < (MAX_CHAR-1) - count; i++){
            printf("  ");
            if (space == 2){
                printf(" "); 
                space = 0;
            }
            space++;
        }
        printf("  ");
        printf("%s", str);
        printf("\n");
    }
    
    fclose(fp);
    return 0;
}