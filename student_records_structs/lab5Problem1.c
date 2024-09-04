// Henry Ngo 
// Lab 5 Problem 1 
// This program will read from a file and store it into structs of array

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_STUDENTS = 100; 
const int MAX_CHAR = 1000; 

struct Struct_Student_Info{
    char StudentName[100]; 
    int ID; 
    float Score;
};

// Must pass structs by pointers to modify the struct, which is just the address of the struct, 
// Not possible to have array returning functions or passing by reference
void Display(struct Struct_Student_Info *s, int count); 
void SortByScore(struct Struct_Student_Info *s, int count); 

int main(){
    // declares an array of structs 
    struct Struct_Student_Info student[MAX_STUDENTS];  
    FILE *fp; 
    char *filename = "student.csv";
    char row[MAX_CHAR];
    char *token; 
    char temp[MAX_CHAR];
    fp = fopen(filename, "r"); 
    int count = 0; 

    // ignores the header or first line in the cvs file
    // fgets arugments(source, length, file stream)
    fgets(row, MAX_CHAR, fp);
    while(fgets(row, MAX_CHAR, fp)){
        token = strtok(row, ",");
        while(token != NULL){
            strcpy(student[count].StudentName, token); 
            token = strtok(NULL,",");  
            strcpy(temp, token);
            // atoi converts string of numbers to int type 
            student[count].ID = atoi(temp);
            token = strtok(NULL,","); 
            strcpy(temp, token);
            // atof converts string of numbers to float type 
            student[count].Score = atof(temp);
            token = strtok(NULL,",");  
        }
        count++;    
    }
    //arugments: array of student structs, total students/structs 
    SortByScore(student, count);
    //arugments: array of student structs, total students/structs 
    // Since student array is passed as a pointer to address, and not passed by value
    // it can be modified by a function and a another function will have access to the 
    // modified data
    Display(student, count);
    fclose(fp); 
    return 0;  
}

void SortByScore(struct Struct_Student_Info *s, int count){
    struct Struct_Student_Info temp[1];
    // sorts in ascending order
    for (int i = 0; i < count-1; i++){
        for (int j = 0; j < count-1; j++){
            if(s[j].Score > s[j+1].Score){
                temp[0] = s[j+1]; 
                s[j+1] = s[j];
                s[j] = temp[0];           
            }      
        }
    }

    // if score is the same, compare the name
    for (int i = 0; i < count-1; i++){
        for (int j = 0; j < count-1; j++){
            if(strcmp(s[j].StudentName, s[j+1].StudentName) > 0 && s[j].Score == s[j+1].Score){
                temp[0] = s[j+1]; 
                s[j+1] = s[j];
                s[j] = temp[0];            
            }      
        }
    } 
}

void Display(struct Struct_Student_Info *s, int count){
    for (int i = 0; i < count; i++){
        printf("%s %d %0.2f\n", s[i].StudentName, s[i].ID, s[i].Score);
    }
}
