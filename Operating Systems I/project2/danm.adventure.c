#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

main(){
	/************
	INTRODUCTION 
	************/
	printf("Welcome to ADVENTURE!\n");
	printf("This is a text based game in which you must\n");
	printf("reach the END room from the START room you\n");
	printf("begin in. To move through rooms, simply type\n");
	printf("the name of one of the possible connecting\n");
	printf("rooms. Best of luck!\n\n");


	char *pick[7];		//declares the array for the 7 random rooms
	int flag[10];		//declares the flag int array
	
	// Make directory with name danm.room.pID
	char directory[1024] = "danm.rooms.";
	char pID[32];
	int pint = getpid();
	// Change pID into a string.
	sprintf(pID, "%d", pint);
	// Add it to the end of directory.
	strcat(directory, pID);
	// Make directory with that name.
	mkdir(directory, 0777);
	
	
	// Initializes the 10 rooms to choose from later.
	char *rooms[] = { "Agrestic", "RenMar", "Seattle", "Dearborn", "Connecticut",
					"Copenhagen", "NYC", "Manhattan", "SanDiego", "Tijuana" };
	
	int i;				//declare i for use in loops
	int r;				//declare r to use for random values
	
	// Fill the flag array with zeroes.
	for (i = 0; i < 10; i++){
		flag[i] = 0;
	}
	
	// VERY IMPORTANT:
	// Makes each run random as opposed to same results.
	srand (time(NULL)); 
	
	/***********
	CHOOSE ROOMS 
	************/
	
	// The following for loop is implemented to
	// check if the random number that was picked
	// has already been used. If it has, it will
	// run through the while loop and pick another.
	// If it hasn't been used, it will exit the while
	// loop and continue.
	for (i = 0; i < 7; i++){
		int flagval = 0;
		while(flagval == 0){
			r = rand() % 10;
			if(flag[r] == 0){
				flagval = 1;
			}
		}
		
		// Flag the location of where the first number
		// is located with a 1, and get the room from
		// rooms[r] into pick[i]. That picks the random
		// room located at point r and saves it in a new array.
		flag[r] = 1;
		pick[i] = rooms[r];
	}

	int rando[7];
	int flag2[7]; 
	// Fill the rando array with zeroes.
	for (i = 0; i < 7; i++){
		rando[i] = 0;
		flag2[i] = 0;
	}

	// The following for/if/while loops are
	// implemented to set a random number of
	// connections for each room, anywhere
	// between 3 and 6 connections each.
	int connum[7];
	for (i = 0; i < 7; i++){
		int flagval = 0;
		while (flagval == 0){
			connum[i] = rand() % 7;
			if (connum[i] >= 3)
				flagval = 1;
		}
	}

	int j, x, temp;
	int cnt[7];
	int connects[7][7];
	
	// Fills connects array with all zeroes.
	for (i = 0; i < 7; i++){
		for (j = 0; j < 7; j++){
			connects[i][j] = 0;
		}
	}
	// Fills the cnt array with all zeroes.
	for (i = 0; i < 7; i++){
		cnt[i] = 0;
	}
	
	
	for (i = 0; i < 7; i++){
		// Reset flag2 to zeroes every time.
		for (j = 0; j < 7; j++){
			flag2[j] = 0;
		}
		// Loop thorough the # of connections.
		for (x = 0; x < connum[i]-1; x++){
		int flagv = 0;
			while (flagv == 0){	
				temp = rand() % 7;
				// Checks if it's already been picked
				// and if it is making a connection
				// with itself.
				if((flag2[temp] == 0) && (temp != i)){
					flagv = 1;
					cnt[temp]++;
					cnt[i]++;
				}
			}
			flag2[temp] = 1;
			// Set the connection, and make sure
			// it is also connected back to the
			// original room.
			connects[i][temp] = 1;
			connects[temp][i] = 1;

		}
	}
	
	/**************
	MAKE ROOM FILES
	***************/
	
	// Counter variables to keep track of
	// connections.
	int countCon[7], c;
	/*********
	* ROOM 1 *
	*********/
	char r1[62];						//declare r1 array
	char room1[128] = "/room1";			//declare room1 array
	c = 0;								//set counter to 0
	strcpy(r1, directory);				//copy directory to r1
	strcat(r1, room1);					//tag the room# at the end of r1
	snprintf(room1, sizeof(room1), r1, pint);
	FILE *f1 = fopen(room1, "w");		//open respective file
	// The following prints the room name, connections,
	// and room_type to the respective file.
	fprintf(f1, "ROOM NAME: %s\n", pick[0]);
	int ct = 1;
	for(i = 0; i < 7; i++){
		if(connects[0][i] == 1){
			fprintf(f1, "CONNECTION %d: %s\n", ct, pick[i]);
			ct++;
			c++;
		}
	}
	countCon[0] = c;	//put the counter into the array
	fprintf(f1, "ROOM TYPE: START_ROOM");
	fclose(f1);
	
	
	/*********
	* ROOM 2 *
	*********/
	char r2[62];
	char room2[128] = "/room2";
	c = 0;
	strcpy(r2, directory);
	strcat(r2, room2);
	snprintf(room2, sizeof(room2), r2, pint);
	
	FILE *f2 = fopen(room2, "w");
	fprintf(f2, "ROOM NAME: %s\n", pick[1]);
	ct = 1;
	for(i = 0; i < 7; i++){
		if(connects[1][i] == 1){
			fprintf(f2, "CONNECTION %d: %s\n", ct, pick[i]);
			ct++;
			c++;
		}
	}
	countCon[1] = c;
	fprintf(f2, "ROOM TYPE: MID_ROOM");
	fclose(f2);
	
	
	/*********
	* ROOM 3 *
	*********/
	char r3[62];
	char room3[128] = "/room3";
	c = 0;
	strcpy(r3, directory);
	strcat(r3, room3);
	snprintf(room3, sizeof(room3), r3, pint);
	
	FILE *f3 = fopen(room3, "w");
	fprintf(f3, "ROOM NAME: %s\n", pick[2]);
	ct = 1;
	for(i = 0; i < 7; i++){
		if(connects[2][i] == 1){
			fprintf(f3, "CONNECTION %d: %s\n", ct, pick[i]);
			ct++;
			c++;
		}
	}
	countCon[2] = c;
	fprintf(f3, "ROOM TYPE: MID_ROOM");
	fclose(f3);
	
	
	/*********
	* ROOM 4 *
	*********/
	char r4[62];
	char room4[128] = "/room4";
	c = 0;
	strcpy(r4, directory);
	strcat(r4, room4);
	snprintf(room4, sizeof(room4), r4, pint);
	
	FILE *f4 = fopen(room4, "w");
	fprintf(f4, "ROOM NAME: %s\n", pick[3]);
	ct = 1;
	for(i = 0; i < 7; i++){
		if(connects[3][i] == 1){
			fprintf(f4, "CONNECTION %d: %s\n", ct, pick[i]);
			ct++;
			c++;
		}
	}
	countCon[3] = c;
	fprintf(f4, "ROOM TYPE: MID_ROOM");
	fclose(f4);
	

	/*********
	* ROOM 5 *
	*********/
	char r5[62];
	char room5[128] = "/room5";
	c = 0;
	strcpy(r5, directory);
	strcat(r5, room5);
	snprintf(room5, sizeof(room5), r5, pint);
	
	FILE *f5 = fopen(room5, "w");
	fprintf(f5, "ROOM NAME: %s\n", pick[4]);
	ct = 1;
	for(i = 0; i < 7; i++){
		if(connects[4][i] == 1){
			fprintf(f5, "CONNECTION %d: %s\n", ct, pick[i]);
			ct++;
			c++;
		}
	}
	countCon[4] = c;
	fprintf(f5, "ROOM TYPE: MID_ROOM");
	fclose(f5);
	

	/*********
	* ROOM 6 *
	*********/
	char r6[62];
	char room6[128] = "/room6";
	c = 0;
	strcpy(r6, directory);
	strcat(r6, room6);
	snprintf(room6, sizeof(room6), r6, pint);
	
	FILE *f6 = fopen(room6, "w");
	fprintf(f6, "ROOM NAME: %s\n", pick[5]);
	ct = 1;
	for(i = 0; i < 7; i++){
		if(connects[5][i] == 1){
			fprintf(f6, "CONNECTION %d: %s\n", ct, pick[i]);
			ct++;
			c++;
		}
	}
	countCon[5] = c;
	fprintf(f6, "ROOM TYPE: MID_ROOM");
	fclose(f6);
	
	
	/*********
	* ROOM 7 *
	*********/
	char r7[62];
	char room7[128] = "/room7";
	c = 0;
	strcpy(r7, directory);
	strcat(r7, room7);
	snprintf(room7, sizeof(room7), r7, pint);
	
	FILE *f7 = fopen(room7, "w");
	fprintf(f7, "ROOM NAME: %s\n", pick[6]);
	ct = 1;
	for(i = 0; i < 7; i++){
		if(connects[6][i] == 1){
			fprintf(f7, "CONNECTION %d: %s\n", ct, pick[i]);
			ct++;
			c++;
		}
	}
	countCon[6] = c;
	fprintf(f7, "ROOM TYPE: END_ROOM");
	fclose(f7);
	
	/************
	  PLAY GAME
	************/
	
	// Variables needed to play game.
	int finalc = 0, win = 0, current = 0, flag0 = 0, count = 0;
	char *final[50];
	char user[64];
	char cur[32] = "/room1";
	char ran[1024] = "";
	
	// Copy directory into ran.
	strcat(ran, directory);
	
	// Setting win as the win condition.
	while(win == 0){
		// Reset ran to directory.
		strcpy(ran, directory);
		// Add the room number to the end.
		strcat(ran, cur);
		FILE *fptr = fopen(ran, "r");	//open file
		char line[256] = "";			//line variable to save the line
		char *token;					//token variable
		count = 0;
		// While it gets a line from the file...
		while(fgets(line, sizeof(line), fptr)){
			token = strtok(line, ": ");	//get the first word
			token = strtok(NULL, ": "); //get the second word
			token = strtok(NULL, "\n"); //get the third word (name, connection, or room type)
			count++;					//incremenet count
			if(count == 1){
				// When count is one, we are on the first
				// line, meaning that is the name of the room.
				printf("\nCURRENT LOCATION: %s", token); 
				printf("\nPOSSIBLE CONNECTIONS: ");
			}else if(count == countCon[current]+2){
				// This makes sure to ignore the ROOM_TYPE
				// field and not include it in connections.
			}else{
				// Print out all of the remaining tokens,
				// which are going to be the connections.
				if(count > 2){
					printf(", ");
				}
				printf("%s", token);
			}
		// Close the file after using it.
		}fclose(fptr);
		
		// Reset flag0 to zero.
		flag0 = 0;
		while(flag0 == 0){
			// Prompt the user to enter where they want to go.
			printf("\n\nWHERE TO?>");
			scanf("%s", &user);
			// The following for loop will compare the user input to
			// the 7 available names, as well as if there is supposed
			// to be a connection there. If so, you're good.
			for(i = 0; i < 7; i++){
				if((connects[current][i] == 1) && (strcmp(user, pick[i]) == 0)){
					current = i;
					flag0 = 1;
					final[finalc] = pick[i];
					finalc++;
				}
			}
			// But if not, spit out the error message and try again.
			if(flag0 == 0)
				printf("HUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.");
		}

		// This long if statement will set the 
		// cur to the current room to be used at
		// the top of the while loop. This is based
		// on the current locaiton of the player.
		if(current == 0){
			strcpy(cur, "/room1");
		}else if(current == 1){
			strcpy(cur, "/room2");
		}else if(current == 2){
			strcpy(cur, "/room3");
		}else if(current == 3){
			strcpy(cur, "/room4");
		}else if(current == 4){
			strcpy(cur, "/room5");
		}else if(current == 5){
			strcpy(cur, "/room6");
		}else if(current == 6){
			strcpy(cur, "/room7");
		}
		
		// Win condition.
		if(strcmp(user, pick[6]) == 0)
			win = 1;
	}
	// Last, but not least, the winning statement, with
	// how many steps and what the path was.
	printf("\nYOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", finalc);
	for(i = 0; i < 50; i ++){
		if(final[i] != NULL)
			printf("%s\n", final[i]);
	}
}
