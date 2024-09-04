// Henry Ngo 
// Lab 3 Problem 1 
// This program will print the reverse of a given array

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, *arr, i;
    //getting the size of array
    scanf("%d", &n);
    arr = (int*) malloc(n * sizeof(int));

    //getting the element of the array
    for(i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }

    //TODO: Write the logic to reverse the array "arr" here  
    int temps[n]; 
    for (int i = 0; i < n; i++){
        temps[i] = arr[n-i-1];    
    }
    for (int i = 0; i < n; i++){
        arr[i] = temps[i];
    }
    
    //END TODO
      
    // Printing the resulting reversed array
    for(i = 0; i < n; i++)
        printf("%d ", *(arr + i));
    printf("\n");
    return 0;
}