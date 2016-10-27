/*********************************************
* Program name: smallsh.c
* Author: Mihai Dan
* Date 11/15/2015
* Compile: gcc -std=c99 -o smallsh.c smallsh
**********************************************/
#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

/* Global status variable */
volatile sig_atomic_t status = -8;

/* CTRL-C Catch */
volatile sig_atomic_t run = 1;

/********************************************************
* Function: endHandler()
* Parameters: n/a
* Description: Sets the run variable to 1. Used whenever
*			   the CTRL-C signal is caught.
********************************************************/
void endHandler(){
	run = 1;
	printf("\n");
}

/********************************************************
* Function: childEnd()
* Parameters: n/a
* Description: Waits for the background process to finish
*			   and displays the exit value.
********************************************************/
void childEnd(){
	int status2;
	// Wait for the process to finish.
	pid_t pid = wait(&status2);
	
	// Print exit message.
	if((status2 == 15) || (status2 == 9))
		printf("background pid %d is done: terminated by signal %d\n", pid, status2);
	else
		printf("background pid %d is done: exit value %d\n", pid, status2);
	// Return.
	return;
}

/****************************************************************
* Function: terminateFunc(int status)
* Parameters: status
* Description: If a foreground process is stopped by CTRL-C,
*			   this function will catch it, return the exit value.
*****************************************************************/
void terminateFunc(){
	int status3;
	
	// Get the PID and status.
	pid_t pid = wait(&status3);
	// Kill the process.
	kill(pid, status3);
	// Print exit message.
	printf("terminated by signal %d\n", status3);
	return;
}

/*****************************************************************
* Function:    execFunction(int length, char user[length], int status)			
* Parameters:  length, user[length], status
* Description: The function takes the user input and sends it to
*			   bash for processing, unless it is not a recognized
*			   command. If it is an unrecognised command, and error
*			   message will be displayed.
******************************************************************/
int execFunction(int length, char user[length], int status){
	/*  Terminate if CTRL-C caught.  */
	if(signal(SIGINT, terminateFunc))
		status = 2;

	/*  Make a copy of the user input.  */
	char usercpy[length];
	for(int i = 0; i < length; i++){
		usercpy[i] = user[i];
	}

	// Get the number of spaces in each argument,
	// ignoring spaces that are followed by other
	// spaces, and the last space followed by the
	// null character.
	int i = 0, numSpaces = 1;
	while(user[i] != '\0'){
		if((user[i] == ' ') && (user[i+1] != '\0') && (user[i+1] != ' ')){
			numSpaces++;
		}
		i++;
	}
	
	/*  Tokenize the user input by the number of spaces.  */
	// Initialize args to save each argument and a null character.
	char *args[numSpaces+1];
	char *token;
	// Loop through size of the args...
	for(int i = 0; i < numSpaces+1; i++){
		// Save the first argument in args[0].
		if(i == 0){
			token = strtok(user, " ");
			args[i] = token;
		// Save the following arguments in args[i].
		}else if(i < numSpaces){
			token = strtok(NULL, " ");
			args[i] = token;
		// Set the last character to null.
		}else{
			args[i] = '\0';
		}
	}

	/*  User command taken and exec()'ed after fork().  */
	// Get the pID's for the parent and child.
	pid_t parentPID = getpid();
	pid_t childPID = fork();
	
	// If the childPID is -1, there was an error.
	if(childPID == -1){
		printf("Process failed.\n");
	// Else, you are in the parent process.
	}else if(childPID > 0){
		// Wait for child process to end.
		waitpid(childPID, &status, 0);
	// Else, childPID = 0 and you are in the child.
	}else{
		if((execvp(args[0], args)) == 0){
			// If it returns no error, perform function.
		}else{
			printf("Command not found: %s\n", usercpy);
			exit(1);
		}
	}
	return status;
}

/*****************************************************************
* Function:    inputRed(int length, char user[length], intstatus)			
* Parameters:  length, user[length], status
* Description: Redirects input to specified file.
******************************************************************/
int inputRed(int length, char user[length], int status){
	/*  Terminate if CTRL-C caught.  */
	if(signal(SIGINT, terminateFunc))
		status = 2;

	// Get the number of spaces in each argument,
	// ignoring spaces that are followed by other
	// spaces, and the last space followed by the
	// null character.
	int i = 0, numSpaces = 1;
	while(user[i] != '\0'){
		if((user[i] == ' ') && (user[i+1] != '\0') && (user[i+1] != ' ')){
			numSpaces++;
		}
		i++;
	}
	
	/*  Tokenize the user input by the number of spaces.  */
	// Initialize args to save each argument and a null character.
	char *args[numSpaces+1];
	char *token;
	char *fileName;
	// Loop through size of the args...
	for(int i = 0; i < numSpaces+1; i++){
		// Save the first argument in args[0].
		if(i == 0){
			token = strtok(user, " ");
			args[i] = token;
		// Save the following arguments in args[i].
		}else if(i < numSpaces){
			token = strtok(NULL, " ");
			args[i] = token;
		// Get file name from token, then set the
		// end of the args array to \0, leaving only
		// the command stored within.
		}else{
			fileName = token;
			args[i-1] = '\0';
			args[i-2] = '\0';
		}
	}
	
	/*  User command taken and exec()'ed after fork().  */
	// Get the pID's for the parent and child.
	pid_t parentPID = getpid();
	pid_t childPID = fork();
	
	// Declare redIn, to be used with dup2 below.
	int redIn = -1;
	redIn = open(fileName, O_RDONLY);
	
	// If the childPID is -1, there was an error.
	if(childPID == -1){
		printf("Process failed.\n");
	// Else, you are in the parent process.
	}else if(childPID > 0){
		waitpid(childPID, &status, 0);
	// Else, childPID = 0 and you are in the child.
	}else{
	// Check if the file exists.
		if(access(fileName, F_OK) != -1){
			// Make sure redIn gets a value.
			if(redIn == -1)
				redIn = open(fileName, O_RDONLY);
			if(redIn == -1)
				exit(127);
			// Redirect input.
			dup2(redIn, 0);
			close(redIn);
			execvp(args[0], args);
		}else{
			printf("%s: no such file or directory\n", fileName);
		}
	}
	return status;
}

/*****************************************************************
* Function:    outputRed(int length, char user[length], intstatus)			
* Parameters:  length, user[length], status
* Description: 
*			   
*
******************************************************************/
int outputRed(int length, char user[length], int status){
	/*  CTRL-C Catch  */
	if(signal(SIGINT, terminateFunc))
		status = 2;

	// Get the number of spaces in each argument,
	// ignoring spaces that are followed by other
	// spaces, and the last space followed by the
	// null character.
	int i = 0, numSpaces = 1;
	while(user[i] != '\0'){
		if((user[i] == ' ') && (user[i+1] != '\0') && (user[i+1] != ' ')){
			numSpaces++;
		}
		i++;
	}
	
	/*  Tokenize the user input by the number of spaces.  */
	// Initialize args to save each argument and a null character.
	char *args[numSpaces+1];
	char *token;
	char *fileName;
	// Loop through size of the args...
	for(int i = 0; i < numSpaces+1; i++){
		// Save the first argument in args[0].
		if(i == 0){
			token = strtok(user, " ");
			args[i] = token;
		// Save the following arguments in args[i].
		}else if(i < numSpaces){
			token = strtok(NULL, " ");
			args[i] = token;
		// Set the last character to null.
		}else{
			fileName = token;
			args[i-1] = '\0';
			args[i-2] = '\0';
		}
	}
	
	/*  User command taken and exec()'ed after fork().  */
	// Get the pID's for the parent and child.
	pid_t parentPID = getpid();
	pid_t childPID = fork();
	
	int redOut = -1;
	redOut = open(fileName, O_WRONLY);
	
	// If the childPID is -1, there was an error.
	if(childPID == -1){
		printf("Process failed.\n");
	// Else, you are in the parent process.
	}else if(childPID > 0){
		waitpid(childPID, &status, 0);
	// Else, childPID = 0 and you are in the child.
	}else{
		// Check if the file exists...
		if(access(fileName, F_OK) != -1){
		// Following if statements make sure that
		// redOut got a varaible.
			if(redOut == -1)
				redOut = open(fileName, O_WRONLY);
			if(redOut == -1)
				exit(127);
			// Redirect output.
			dup2(redOut, 1);
			close(redOut);
			execvp(args[0], args);
		// ...if not, error message.
		}else{
			printf("%s: no such file or directory\n", fileName);
		}
	}
	return status;
}


/*****************************************************************
* Function:    execBackFunc(int length, char user[length])			
* Parameters:  length, user[length]
* Description: The function takes the user input and sends it to
*			   bash for processing, unless it is not a recognized
*			   command. If it is an unrecognised command, and error
*			   message will be displayed. This function will send
*              processes to the background.
******************************************************************/
void execBackFunc(int length, char user[length]){
	/*  Signal catches.  */
	signal(SIGINT, SIG_IGN);
	signal(SIGCHLD, childEnd);
	
	/*  Make a copy of the user input.  */
	char usercpy[length];
	for(int i = 0; i < length; i++){
		usercpy[i] = user[i];
	}

	// Get the number of spaces in each argument,
	// ignoring spaces that are followed by other
	// spaces, and the last space followed by the
	// null character.
	int i = 0, numSpaces = 1;
	while(user[i] != '\0'){
		if((user[i] == ' ') && (user[i+1] != '\0') && (user[i+1] != ' ')){
			numSpaces++;
		}
		i++;
	}
	
	/*  Tokenize the user input by the number of spaces.  */
	// Initialize args to save each argument and a null character.
	char *args[numSpaces];
	char *token;
	// Loop through size of the args...
	for(int i = 0; i < numSpaces+1; i++){
		// Save the first argument in args[0].
		if(i == 0){
			token = strtok(user, " ");
			args[i] = token;
		// Save the following arguments in args[i].
		}else if(i < numSpaces){
			token = strtok(NULL, " ");
			args[i] = token;
		// Set the last character to null.
		}else{
			args[i-1] = '\0';
		}
	}
	
	//signal(SIGCHLD, childEnd);
	/*  User command taken and exec()'ed after fork().  */
	// Get the pID's for the parent and child.
	pid_t parentPIDB = getpid();
	pid_t childPIDB = fork();
	
	// Print the pid before execution.
	if(childPIDB > 0)
		printf("background pid is %d\n", childPIDB);
	
	// In/Out redirection variables.
	int devOut = -1;
	int devIn = -1;
	
	// If the childPID is -1, there was an error.
	if(childPIDB == -1){
		printf("Process failed.\n");
	// Else, you are in the parent process.
	}else if(childPIDB > 0){
	// Else, childPID = 0 and you are in the child.
	}else{
	// Same check as above, make sure they both get
	// a different variable than what previously set.
		if((devIn == -1) && (devOut == -1)){
			devOut = open("/dev/null", O_WRONLY);
			devIn = open("/dev/null", O_RDONLY);
		}
		if((devIn == -1) && (devOut == -1))
			exit(127);
		// Redirect output and input.
		dup2(devOut, 1);
		dup2(devIn, 0);
		close(devOut);
		close(devIn);
		// Execute.
		execvp(args[0], args);
	}
	return;
}

/***************************************************************
* Function:    main()			
* Parameters:  n/a
* Description: Will run the while loop to keep the shell alive,
*			   check for user input and handle accordingly.
****************************************************************/
void main(){
	while(1){
		/* CTRL-C Catch */
		signal(SIGINT, endHandler);
		// Character array to store user input.
		char user[2049] = {0};
		char *token;
		// Integer to keep track of length array.
		int length;
		// Read user from user.
		printf(": ");
		fgets(user, 2048, stdin);
		length = strlen(user);
		user[length-1] = '\0';
		
		/*  BACKGROUND Process  */
		if((user[length-2] == '&') && (user[length-3] == ' ')){
			// If exit, break out of while loop.
			if((strcmp(user, "exit")) == 0){
				break;
			// If cd, change directories...
			}else if((user[0] == 'c') && (user[1] == 'd') && (user[length-2] == '&')){
				// ...do nothing.
			// If status, show status of last process...
			}else if((user[0] == 's') && (user[1] == 't') && (user[2] == 'a') && (user[3] == 't') && (user[4] == 'u') && (user[5] == 's')){
				// ...do nothing.
			// If first char is #, then...
			}else if(user[0] == '#'){
				// ...do nothing because it is a comment.
			// If nothing was entered...
			}else if(user[0] == '\0'){
				// ...do nothing because nothing was entered.
			// Else, command is not understood.
			}else{
				// Call to exec function.
				execBackFunc(length, user);
				//printf("Command not found: %s\n", user);
			}
		/*  FOREGROUND Process  */
		}else{
			// If exit, break out of while loop.
			if((strcmp(user, "exit")) == 0){
				break;
			// If cd, change directories.
			}else if((user[0] == 'c') && (user[1] == 'd')){
				if(user[2] != ' '){
					// If there is no space, take me home.
					chdir(getenv("HOME"));
				}else{
					// Else, change to the specified directory.
					token = strtok(user, " ");
					token = strtok(NULL, " ");
					chdir(token);
				}
			// If status, show status of last process.
			}else if((strcmp(user, "status")) == 0){
				// Catch for the termination signal.
				if(status != 2){
					// Catch for no prior processes.
					if(status != -8){
						printf("exit value %d\n", status/256);
					}else{
						printf("No prior process.\n");
					}
				}else{
					printf("terminated by signal %d\n", status);
				}
			// If first char is #, then...
			}else if(user[0] == '#'){
				// ...do nothing because it is a comment.
			// If nothing was entered...
			}else if(user[0] == '\0'){
				// ...do nothing because nothing was entered.
			// If > found, handle output redirect.
			}else if(strchr(user, '>')){
				status = outputRed(length, user, status);
			// If < found, handle input redirect.
			}else if(strchr(user, '<')){
				status = inputRed(length, user, status);
			// Else, command is not understood.
			}else{
				// Call to exec function.
				status = execFunction(length, user, status);
			}
		}
	}
	return;
}