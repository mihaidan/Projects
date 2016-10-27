/* CS261- Assignment 1 - Q.5*/
/* Name: Mihai Dan, Marc Ohlmann
 * Date: 10/8/2014
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void studly(char* word){
     /*Convert to studly caps*/
	int alternating = 1;
	int i = 0;

	while(i < strlen(word))
	{
		if(alternating == 0)
		{
			word[i] = tolower(word[i]);
			alternating = 1;
		}
		else
		{
			word[i] = toupper(word[i]);
			alternating = 0;
		}
		i++;
	}

	return;
}

int main(){
    /*Read word from the keyboard using scanf*/
	char* word = malloc(sizeof(char));
	printf("Please enter a word: \n");
	scanf("%s", word);
   
    /*Call studly*/
	studly(word);

    /*Print the new word*/
    	printf("%s\n", word);

	return 0;
}
