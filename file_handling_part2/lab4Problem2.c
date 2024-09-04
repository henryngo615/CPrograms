// Henry Ngo 
// Lab 4 Problem 2
// This lab will read from a file and compare it to user input; 

#include <stdio.h>
#include <string.h>

const int MAX_LENGTH = 100; 

int main(){
    char user[MAX_LENGTH]; 
    char password[MAX_LENGTH]; 
    float balance; 
    int match = 0; 
    

    char file_user[MAX_LENGTH]; 
    char file_password[MAX_LENGTH]; 
    
    
    FILE *fp;
    char ch[100]; 
    char *filename = "userdata.txt"; 
    fp = fopen(filename, "r"); 

    printf("Username: ");
    scanf("%s", user); 

    printf("Password: ");
    scanf("%s", password); 

    // fgets reads first line of file
    while (fgets(ch, sizeof(ch), fp) && match != 1){
        sscanf(ch, "%s %s %f", file_user, file_password, &balance);
        // strcmp method compares the two string
        if (!strcmp(user, file_user) && !strcmp(password, file_password)){
            printf("The amount is: %0.2f\n", balance);
            match = 1;
        }   
    }

    if (match == 0){
        printf("username/password mismatch!!!\n");
    }
    
    fclose(fp); 
    



    
}