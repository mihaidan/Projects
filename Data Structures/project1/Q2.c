/* CS261- Assignment 1 - Q.2*/
/* Name: Marc Ohlmann, Mihai Dan
 * Date: 10/8/2014
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
    *a = 2*(*a);
    /*Set b to half its original value*/
    *b = (*b)/2;
    /*Assign a+b to c*/
    c = (*a)+(*b);
    /*Return c*/
    return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 7, 8, 9 respectively*/
    int x = 7, y = 8, z = 9;
    /*Print the values of x, y and z*/
    printf("x = %d, y = %d, z = %d \n", x, y, z);
    /*Call foo() appropriately, passing x,y,z as parameters*/
    int var = foo(&x, &y, z);
    /*Print the value returned by foo*/
    printf("value of foo is: %d \n", var); 
    /*Print the values of x, y and z again*/
    printf("x = %d, y = %d, z = %d \n", x, y, z);
    /*Is the return value different than the value of z?  Why?*/
    /*Yes, because we did not pass the value of z as a pointer, therefore it is not affected outside of the function.*/
    return 0;
}
    
    
