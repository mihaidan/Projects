/* CS261- Assignment 1 - Q.3*/
/* Name: Mihai Dan, Marc Ohlmann
 * Date: 10/8/2014
 */
 
#include <stdio.h>
#include <stdlib.h>

void sort(int* number, int n){
     /*Sort the given array number , of length n*/
     int i, j, temp, temp2;
     for(i = n-1; i>0; i--){
     	for(j=0; j<i; j++){
     	if(number[j] > number[j+1]){
	    temp = number[j];
	    temp2 = number[j+1];
	    number[j] = temp2;
 	    number[j+1] = temp;
	}
     }
   }	
}

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;    
    /*Allocate memory for an array of n integers using malloc.*/
    int *array = malloc(n*sizeof(int*));
    /*Fill this array with random numbers between 0 and n, using rand().*/
    int i;
    for(i = 0; i<n; i++){
         array[i] = rand() % n + 1;
    }
    /*Print the contents of the array.*/
    for (i = 0; i<n; i++){
       printf(" %d", array[i]);
    }
    printf("\n");
    /*Pass this array along with n to the sort() function.*/
    sort(array, n);
    /*Print the contents of the array.*/
    printf("sorted array: \n");
    for(i=0; i<n; i++){
       printf(" %d", array[i]);
    }
    printf("\n");
    return 0;
}
