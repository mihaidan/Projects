/*********************************************
* Program name: otp_dec.c
* Author: Mihai Dan
* Date 12/1/2015
* Compile: gcc -std=c99 -o otp_dec otp_dec.c
**********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#define h_addr h_addr_list[0]

/***************************************************************
* Function:    main(int argc, char *argv[])			
* Parameters:  argc, *argv[]
* Description: Captures the text from the cipher and key files,
			   stores them in and array, and sends them to the
			   daemon to be processed. The original text will be
			   returned based on the key.
****************************************************************/
int main(int argc, char *argv[]){
	
	// Variable definitions.
	int portNum, textLen, keyLen;
	char textArr[2048];
	char keyArr[2048];
	FILE* textFile = NULL;
	FILE* keyFile = NULL;

	// Check if the right amount of arguments entered.
	if(argc != 4){
		printf("Please follow the format \"otp_dec <plaintext> <key> <port>\"\n");
		exit(1);
	}
	
	// Check arguments 2 and 3 to see if they open
	// with a file pointer.
	if((textFile = fopen(argv[1], "r")) && (keyFile = fopen(argv[2], "r"))) {
		portNum = atoi(argv[3]);
		
		// Get the text into textArr.
		while(fgets(textArr, sizeof(textArr), textFile)){
			textLen = strlen(textArr);
		}
		
		// Get the key into keyArr.
		while(fgets(keyArr, sizeof(keyArr), keyFile)){
			keyLen = strlen(keyArr);
		}
		
		// Close both files.
		fclose(textFile);
		fclose(keyFile);
	}
	
	// Check to see if the key is longer than the text.
	if(textLen > keyLen){
		printf("Error: key '%s' is too short\n", argv[2]);
		exit(1);
	}
	
	// Define socket variables.
	int socketFD, checkKey, checkText;
    struct sockaddr_in serverAddr;
    struct hostent *server;
	
	// Open socket.
	socketFD = socket(AF_INET, SOCK_STREAM, 0);
	if(socketFD < 0){
		printf("Error opening socket.\n");
		exit(1);
	}
	
	// Get the host name using the hostent struct and
	// gethostbyname().
    server = gethostbyname("localhost");
    if (server == NULL) {
        printf("Error: host not found.\n");
        exit(1);
    }
	
	// Make sure the server address is blank.
    bzero((char *) &serverAddr, sizeof(serverAddr));
	
	// Set server family, port number and address.
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(portNum);
	bcopy((char *) server->h_addr, (char *) &serverAddr.sin_addr.s_addr, server->h_length);
	
	// Connect, and make sure connection was successful.
    if(connect(socketFD, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0){
        printf("Error: could not contact otp_dec_d on port %d\n", portNum);
		exit(2);
	}
	
	/*********************HANDSHAKE**********************/
	// Check to make sure that it is attempting to run on
	// otp_enc_d
	int portCheck = 3, portBack;
	write(socketFD, &portCheck, sizeof(portCheck));
	read(socketFD, &portBack, sizeof(portBack));
	if(portBack < 0){
		printf("Error: could not contact otp_dec_d on port %d\n", portNum);
		exit(1);
	}
	/*********************HANDSHAKE**********************/
	
	// Write the textArr to the socket.
	checkText = write(socketFD, textArr, 2047);
	// Check to make sure write did not fail.
    if((checkText < 0)){
         printf("Error writing data to socket.");
		 exit(1);
	}
	// Write keyArr to socket
	checkKey = write(socketFD, keyArr, 2047);
	// Error check
	if((checkKey < 0)){
         printf("Error writing data to socket.");
		 exit(1);
	}
	
	// Empty the textArr to save encryption.
	bzero(textArr, 2047);
	
	// Read back from the socket and check for success.
	checkText = read(socketFD, textArr, 2047);
	if(checkText < 0){
		printf("Error reading from socket.\n");
		exit(1);
	}
	
	// STDOUT the resulting array.
	printf("%s", textArr);
	// Close the socket.
	close(socketFD);
	// Return 0.
	return 0;

}