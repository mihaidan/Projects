/* CS261- Assignment 1 - Q.4*/
/* Name: Mihai Dan, Marc Ohlmann
 * Date: 10/8/2014
 */
 
#include <stdio.h>
#include <stdlib.h>

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/     
     /* Remember, each student must be matched with their original score after sorting */
	int i = 0;
	int j = 0;
	int tmp1 = 0;
	int tmp2 = 0;
	int tmp3 = 0;
	int tmp4 = 0;

	for(i = n - 1; i < n; i--){
		for(j = 0; j < i; j++){
			if(students[j].id > students[j + 1].id)
			{
				tmp1 = students[j + 1].id;
				tmp2 = students[j + 1].score;
				tmp3 = students[j].id;
				tmp4 = students[j].score;
				students[j + 1].id = tmp3;
				students[j + 1].score = tmp4;
				students[j].id = tmp1;
				students[j].score = tmp2;
			}
		}
	}
	return;
}

int main(){
	int i = 0;
    /*Declare an integer n and assign it a value.*/
	int n = 5;   
    /*Allocate memory for n students using malloc.*/
    	struct student* s = malloc(n*sizeof(struct student));
    /*Generate random IDs and scores for the n students, using rand().*/
	int tmp = 0;
	int check = n;
	int* id_list = malloc(n*sizeof(int));
	
	for(i = 0; i < n; i++){
		id_list[i] = i;
	}
	
	for(i = 0; i < n; i++){
		s[i].score = rand() % 100;
		while(check == n){
			tmp = rand() % n;
			check = id_list[tmp];
		}
		s[i].id = check;
		id_list[tmp] = n;
		check = n;
	}
	 
    /*Print the contents of the array of n students.*/
	printf("ID	Score\n"); 
	for(i = 0; i < n; i++){
		printf("%d	", s[i].id);
		printf("%d\n", s[i].score);
	}
    /*Pass this array along with n to the sort() function*/
    	sort(s, n);
    /*Print the contents of the array of n students.*/
	printf("ID      Score\n");
	for(i = 0; i < n; i++){
	        printf("%d	", s[i].id);     
	        printf("%d\n", s[i].score);
	}
	return 0;
}
