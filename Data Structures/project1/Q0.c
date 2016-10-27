/* CS261- Assignment 1 - Q. 0*/
/* Name: Marc Ohlmann, Mihai Dan
 * Date: 10/8/2014
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
     printf("value pointed to is %d \n", *iptr); 
     /*Print the address pointed to by iptr*/
     printf("address pointed to is %p \n", iptr);
     /*Print the address of iptr itself*/
     printf("address of iptr itself is %p \n", &iptr);
}

int main(){
    
    /*declare an integer x*/
    int x;
    /*print the address of x*/
    printf("the address of x is %p \n", &x);
    /*Call fooA() with the address of x*/
    fooA(&x);
    /*print the value of x*/
    printf("the value of x is %d \n", x);
    return 0;
}
