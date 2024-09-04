// Henry Ngo 
// Lab 3 Problem 2 
// This program will determine if user's string contain vowels

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING 1000
#define  MAX_LETTERS 20 
#define  MAX_WORDS 50

void SortArr(char arr[MAX_WORDS][MAX_LETTERS], int count); 
void PrintArr(char arr[MAX_WORDS][MAX_LETTERS], int count);

int main(){
    char UserString[MAX_STRING]; 
    char *token; 
    char arr[MAX_WORDS][MAX_LETTERS];  
    int count = 0;
    
    printf("Enter a line of text: ");
    fgets(UserString, MAX_STRING , stdin); 
    printf("Words starting with vowels:\n");

    // strtok is a method to split up individual words in a sentence of words
    // toupper is a method to capitalize lowercase characters 
    token = strtok(UserString, " \n");
    while(token != NULL && count < MAX_WORDS){
        char c = token[0];
        if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
            for (int i = 0; i < strlen(token); i++){
                arr[count][i] = toupper(token[i]);
            }
            // Used for print function, terminates when it recognizes a null character
            arr[count][strlen(token)] = '\0';
            count++;               
        }
        token = strtok(NULL, " \n");
    }

    SortArr(arr, count);
    PrintArr(arr, count);
}

// compare two strings, strcmp will return x >= 0 or x <= 0 based on the order, strcpy is a copying method for strings 
void SortArr(char arr[MAX_WORDS][MAX_LETTERS], int count){
    char temp[MAX_LETTERS]; 
    for (int i = 0; i < count-1; i++){
        for (int j = 0; j < count-1-i; j++){
            if(strcmp(arr[j], arr[j+1]) > 0){
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j+1], temp);             
            }      
        }
    }    
}

// iterate through array and prints it out
void PrintArr(char arr[MAX_WORDS][MAX_LETTERS], int count){
    for (int i = 0; i < count; i++){
        printf("%s\n", arr[i]);
    }
}