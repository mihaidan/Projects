/*********************************************
* Program name: otp_enc_d.c
* Author: Mihai Dan
* Date 12/1/2015
* Compile: gcc -std=c99 -o otp_enc_d otp_enc_d.c
**********************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){
	// Set the port number.
	int portNum = atoi(argv[1]);
	
	// Declare variables for sockets and storing variables.
	int socketFD, newSocketFD, textLen, pID;
	char textArr[2048];
	char keyArr[2048];
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLength;

	// Open socket.
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if(socketFD < 0){
		printf("Error opening socket.\n");
		exit(1);
	}
	// Make sure the server address is blank.
    bzero((char *) &serverAddr, sizeof(serverAddr));
	
	// Set server family, port number and address.
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(portNum);
	
	// Bind the socket by the server address and socket.
    if(bind(socketFD, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0){ 
		printf("Error: binding failed.\n");
		exit(1);
	}
	
	// Listen for connections.
	listen(socketFD, 5);
	
	// Get the client length into a variable.
	clientLength = sizeof(clientAddr);
	
	while(1){
		// Set newSocketFD as the accept socket.
		newSocketFD = accept(socketFD, (struct sockaddr *) &clientAddr, &clientLength);
		// Check for success.
		if(newSocketFD < 0){
			printf("Error: accept failed.\n");
			exit(1);
		}
		
		// Fork to allow multiple processes.
		pID = fork();
		
		// If it's below zero, error.
		if(pID < 0){
			printf("Error while forking.\n");
			exit(1);
		}
		
		// You are in the child.
		if(pID == 0){
			// Define more variables.
			int checkKey, checkText, newLineCounter = 0;
			
			/*********************HANDSHAKE**********************/
			int portCheck = 2, portBack;
			read(newSocketFD, &portBack, sizeof(portBack));
			if(portBack == 1){
				portCheck = 2;
				write(newSocketFD, &portCheck, sizeof(portCheck));
			}else{
				portCheck = -7;
				write(newSocketFD, &portCheck, sizeof(portCheck));
				exit(1);
			}
			/*********************HANDSHAKE**********************/
			
			// Read textArr from the accept socket.
			// Empty the textArr to save encryption.
			bzero(textArr, 2047);
			checkText = read(newSocketFD, textArr, 2047);
			// Error check
			if((checkText < 0)){
				 printf("Error reading data from socket.");
				 exit(1);
			}
			
			// Read keyArr from the accept socket.
			// Empty the keyArr to save encryption.
			bzero(keyArr, 2047);
			checkKey = read(newSocketFD, keyArr, 2047);
			// Error check
			if((checkKey < 0)){
				 printf("Error reading key data from socket.");
				 exit(1);
			}
			
			/* MATH */
			// Loop through length of textArr-1
			for(int i = 0; i < strlen(textArr)-1; i++){
				// Variables for the math.
				int textNum, keyNum, cipherNum;
				
				// Decide the value for the character in textArr. 1 cor 15:33
				switch(textArr[i]){
					case 'A': 
						textNum = 0; break;
					case 'B': 
						textNum = 1; break;
					case 'C': 
						textNum = 2; break;
					case 'D': 
						textNum = 3; break;
					case 'E': 
						textNum = 4; break;
					case 'F': 
						textNum = 5; break;
					case 'G': 
						textNum = 6; break;
					case 'H': 
						textNum = 7; break;
					case 'I': 
						textNum = 8; break;
					case 'J': 
						textNum = 9; break;
					case 'K': 
						textNum = 10; break;
					case 'L': 
						textNum = 11; break;
					case 'M': 
						textNum = 12; break;
					case 'N': 
						textNum = 13; break;
					case 'O': 
						textNum = 14; break;
					case 'P': 
						textNum = 15; break;
					case 'Q': 
						textNum = 16; break;
					case 'R': 
						textNum = 17; break;
					case 'S': 
						textNum = 18; break;
					case 'T': 
						textNum = 19; break;
					case 'U': 
						textNum = 20; break;
					case 'V': 
						textNum = 21; break;
					case 'W': 
						textNum = 22; break;
					case 'X': 
						textNum = 23; break;
					case 'Y': 
						textNum = 24; break;
					case 'Z': 
						textNum = 25; break;
					case ' ': 
						textNum = 26; break;
					default:
						printf("Error: Invalid character in file.\n");	//if there was an invalid character used in file 5
						exit(1);	
				}
				
				// Get the value of the characters in keyArr.
				if(keyArr[i] == 'A'){
					keyNum = 0;
				}else if(keyArr[i] == 'B'){
					keyNum = 1;
				}else if(keyArr[i] == 'C'){
					keyNum = 2;
				}else if(keyArr[i] == 'D'){
					keyNum = 3;
				}else if(keyArr[i] == 'E'){
					keyNum = 4;
				}else if(keyArr[i] == 'F'){
					keyNum = 5;
				}else if(keyArr[i] == 'G'){
					keyNum = 6;
				}else if(keyArr[i] == 'H'){
					keyNum = 7;
				}else if(keyArr[i] == 'I'){
					keyNum = 8;
				}else if(keyArr[i] == 'J'){
					keyNum = 9;
				}else if(keyArr[i] == 'K'){
					keyNum = 10;
				}else if(keyArr[i] == 'L'){
					keyNum = 11;
				}else if(keyArr[i] == 'M'){
					keyNum = 12;
				}else if(keyArr[i] == 'N'){
					keyNum = 13;
				}else if(keyArr[i] == 'O'){
					keyNum = 14;
				}else if(keyArr[i] == 'P'){
					keyNum = 15;
				}else if(keyArr[i] == 'Q'){
					keyNum = 16;
				}else if(keyArr[i] == 'R'){
					keyNum = 17;
				}else if(keyArr[i] == 'S'){
					keyNum = 18;
				}else if(keyArr[i] == 'T'){
					keyNum = 19;
				}else if(keyArr[i] == 'U'){
					keyNum = 20;
				}else if(keyArr[i] == 'V'){
					keyNum = 21;
				}else if(keyArr[i] == 'W'){
					keyNum = 22;
				}else if(keyArr[i] == 'X'){
					keyNum = 23;
				}else if(keyArr[i] == 'Y'){
					keyNum = 24;
				}else if(keyArr[i] == 'Z'){
					keyNum = 25;
				}else if(keyArr[i] == ' '){
					keyNum = 26;
				}
				
				// Add them together.
				cipherNum = textNum + keyNum;
				
				// If it's greater than 26, subtract 27.
				if(cipherNum > 26)
					cipherNum = cipherNum - 27;

				printf("");
					
				// Decide what letter to save in the cipher text array.
				if(cipherNum == 0){
					textArr[i] = 'A';
				}else if(cipherNum == 1){
					textArr[i] = 'B';
				}else if(cipherNum == 2){
					textArr[i] = 'C';
				}else if(cipherNum == 3){
					textArr[i] = 'D';
				}else if(cipherNum == 4){
					textArr[i] = 'E';
				}else if(cipherNum == 5){
					textArr[i] = 'F';
				}else if(cipherNum == 6){
					textArr[i] = 'G';
				}else if(cipherNum == 7){
					textArr[i] = 'H';
				}else if(cipherNum == 8){
					textArr[i] = 'I';
				}else if(cipherNum == 9){
					textArr[i] = 'J';
				}else if(cipherNum == 10){
					textArr[i] = 'K';
				}else if(cipherNum == 11){
					textArr[i] = 'L';
				}else if(cipherNum == 12){
					textArr[i] = 'M';
				}else if(cipherNum == 13){
					textArr[i] = 'N';
				}else if(cipherNum == 14){
					textArr[i] = 'O';
				}else if(cipherNum == 15){
					textArr[i] = 'P';
				}else if(cipherNum == 16){
					textArr[i] = 'Q';
				}else if(cipherNum == 17){
					textArr[i] = 'R';
				}else if(cipherNum == 18){
					textArr[i] = 'S';
				}else if(cipherNum == 19){
					textArr[i] = 'T';
				}else if(cipherNum == 20){
					textArr[i] = 'U';
				}else if(cipherNum == 21){
					textArr[i] = 'V';
				}else if(cipherNum == 22){
					textArr[i] = 'W';
				}else if(cipherNum == 23){
					textArr[i] = 'X';
				}else if(cipherNum == 24){
					textArr[i] = 'Y';
				}else if(cipherNum == 25){
					textArr[i] = 'Z';
				}else if(cipherNum == 26){
					textArr[i] = ' ';
				}
				
				// Counter for placing the '\n' at the end.
				newLineCounter++;
			}
			
			// Set a '\n' at the end+1 of the array.
			textArr[newLineCounter+1] == '\n';
				
			/* END MATH */
				
			// Write the textArr back to the socket.
			checkText = write(newSocketFD, textArr, 2047);
			// Check for success.
			if(checkText < 0){
				printf("Error writing to socket.\n");
				exit(1);
			}
			
			// Close sockets.
			close(newSocketFD);
			close(socketFD);
			exit(0);
		}else{
			// Else, just close the new socket.
			close(newSocketFD);
		}
	}
}