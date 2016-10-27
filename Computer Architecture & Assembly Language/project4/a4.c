#include <stdlib.h>
#include <stdio.h>

/*** Reverse an array in place ***/
int func1(int intArr[10]){
	//initialize  variables
	int start = 0, end = 9, temp, i;
	
	//print the initial array
	printf("Original Array: ");
	for(i = 0; i < 10; i++){
		printf("%d ", intArr[i]);
	}
	printf("\n");
	
	//flip the array in places
	for(i = 0; i < 5; i++){
		temp = intArr[start];
		intArr[start] = intArr[end];
		intArr[end] = temp;
		
		//increment start and decrement end
		start++;
		end--;
	}
	
	//print the flipped array
	printf("Reversed Array: ");
	for(i = 0; i < 10; i++){
		printf("%d ", intArr[i]);
	}
	printf("\n");
	//return intArray
	return *intArr;
}

/*** Array Rotation ***/
int func2(int intArr[10]){
	//print the array
	int i;
	printf("Original Array: ");
	for(i = 0; i < 10; i++){
		printf("%d ", intArr[i]);
	}
	printf("\n");
	
	//decide between shifting left or right
	int val;
	printf("Would you like to rotate left or right? (1 - right; 0 - left)\n");
	scanf("%d", &val);
	
	int start = 0, end = 9, temp;
	//shift to the right
	if(val == 1){
		temp = intArr[end];
		for(i = 10; i >= 1; i--){
			intArr[i] = intArr[i-1];
		}
		intArr[start] = temp;
	}
	//shifts to the left
	if(val == 0){
		temp = intArr[start];
		for(i = 0; i <= 10; i++){
			intArr[i] = intArr[i+1];
		}
		intArr[end] = temp;
	}
	//prints the shifted array
	for(i = 0; i < 10; i++){
		printf("%d ", intArr[i]);
	}
	printf("\n");
	//return intArr
	return *intArr;
}

/*** Frequency Table ***/
int func3(char stringArr[]){
	int countArr[128];
	int asciiArr[128];
	int num, i;
	
	//initialize countArr
	for(i = 0; i < 129; i++){
		countArr[i] = 0;
	}
	
	//initialize asciiArr
	for(i = 0; i < 129; i++){
		asciiArr[i] = 0;
	}
	
	//print the string
	printf("This is the string: '%s'\n", stringArr);
	
	//frequency
	for(i = 0; i < 30; i++){
		num = stringArr[i];
		printf("ASCII value = %d ", num);
		countArr[num]++;
		printf("Frequency: %d\n", countArr[i]); 
	}
}

/*** Sieve of Eratosthenes ***/
int func4(){
	int limit, i, j;

	//gets the limit for the Sieve of Eratosthenes
	printf("Please enter an integer: ");
	scanf("%d", &limit);
	
	//sieve array
	int sieve[limit];
	
	//fill the array from 1 to limit
	for(i = 0; i < limit; i++){
		sieve[i] = i+1;
	}
	
	//set 1 as a special
	sieve[0] = 0;
	
	//Sieve of Eratosthenes
	//seeds out the prime numbers
	for(i = 2; i < limit/2; i++){
		for(j = 1; j < limit; j++){
			if(sieve[j] != i && sieve[j]%i == 0){
				sieve[j] = 0;
			}
		}
	}
	
	//print out the prime numbers
	printf("Prime numbers: \n");
	for(i = 0; i < limit; i++){
		//filter the marked numbers
		if(sieve[i] != 0){
			printf("               %d\n", sieve[i]);
		}
	}
}


main(){
	int intArr[10];
	char stringArr[] = "This is a string for testing!";
	
	//fill the intArr array with numbers 0-9
	int i, fill, decision;
	for(i = 0; i < 10; i++){
		intArr[i] = fill+1;
		fill++;
	}
	
	//gives the user options
	printf("Welcome to Assignment 4 by Mihai Dan!\n");
	printf("Here are your options:\n");
	printf("1 - Reverse an array in place.\n");
	printf("2 - Rotate the array.\n");
	printf("3 - Construct a frequency table.\n");
	printf("4 - The Sieve of Eratosthenes.\n");
	printf("0 - Exit.\n");
	scanf("%d", &decision);
	
	if(decision == 0){
		printf("Good bye!\n");
	}
	if(decision == 1){
		func1(intArr);
	}
	if(decision == 2){
		func2(intArr);
	}
	if(decision == 3){
		func3(stringArr);
	}
	if(decision == 4){
		func4();
	}
}
