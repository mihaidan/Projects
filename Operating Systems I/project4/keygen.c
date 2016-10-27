/*********************************************
* Program name: keygen.c
* Author: Mihai Dan
* Date 12/1/2015
* Compile: gcc -std=c99 -o keygen keygen.c
**********************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/***************************************************************
* Function:    main(int argc, char *argv[])			
* Parameters:  argc, *argv[]
* Description: This function takes the keylength provided by the
*			   user and generates n random numbers. Based on the
*			   number generated, the corresponding letter will be
*			   printed out.
****************************************************************/
int main(int argc, char *argv[]){ 
	// Check if the length was entered.
	if(argc < 2){
		printf("No length entered.\n");
		exit(1);
	}
	
	// Get the keyLength into an integer.
	int keyLength = atoi(argv[1]);
	
	// This is so it randomizes it every time.
	srand (time(NULL));
	
	// For loop running through keyLength
	for(int i = 0; i < keyLength; i++){
		// Random number declared.
		int randoNum;
		
		// rand() function to get a number between 0 and 27
		randoNum = rand() % 27;
		
		// Turns the number into the corresponding letter.
		if(randoNum == 0){
			printf("A");
		}else if(randoNum == 1){
			printf("B");
		}else if(randoNum == 2){
			printf("C");
		}else if(randoNum == 3){
			printf("D");
		}else if(randoNum == 4){
			printf("E");
		}else if(randoNum == 5){
			printf("F");
		}else if(randoNum == 6){
			printf("G");
		}else if(randoNum == 7){
			printf("H");
		}else if(randoNum == 8){
			printf("I");
		}else if(randoNum == 9){
			printf("J");
		}else if(randoNum == 10){
			printf("K");
		}else if(randoNum == 11){
			printf("L");
		}else if(randoNum == 12){
			printf("M");
		}else if(randoNum == 13){
			printf("N");
		}else if(randoNum == 14){
			printf("O");
		}else if(randoNum == 15){
			printf("P");
		}else if(randoNum == 16){
			printf("Q");
		}else if(randoNum == 17){
			printf("R");
		}else if(randoNum == 18){
			printf("S");
		}else if(randoNum == 19){
			printf("T");
		}else if(randoNum == 20){
			printf("U");
		}else if(randoNum == 21){
			printf("V");
		}else if(randoNum == 22){
			printf("W");
		}else if(randoNum == 23){
			printf("X");
		}else if(randoNum == 24){
			printf("Y");
		}else if(randoNum == 25){
			printf("Z");
		}else if(randoNum == 26){
			printf(" ");
		}
	}
	// New line character at the end.
	printf("\n");
}
