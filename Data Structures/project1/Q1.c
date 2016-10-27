/* CS261- Assignment 1 - Q.1*/
/* Name: Marc Ohlmann, Mihai Dan
 * Date: 10/8/2014
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
    struct student *s = malloc(10*sizeof(struct student)); 
     /*return the pointer*/
     return s;
}

void generate(struct student* students){
     /*Generate random ID and scores for 10 students, ID being between 1 and 10, scores between 0 and 100*/
	int check = 10;
	int tmp = 0;
	int i = 0;
	int id_list[10];

	for(i = 0; i < 10; i++){
		id_list[i] = i;
	}

	for(i = 0; i < 10; i++){
		students[i].score = rand() % 100;
		while(check == 10){
			tmp = rand() % 10;
			check = id_list[tmp];
		}
		students[i].id = check;
		id_list[tmp] = 10;
		check = 10;
	}
	return;
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	int i = 0;
	printf("ID	Score\n");
	for(i = 0; i < 10; i++)
	{
		printf("%d", students[i].id);
		printf("	");
		printf("%d\n", students[i].score);
	}
	return;
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
	int i = 0;
	int avg = 0;
	int sum = 0;
	int min_score = 100;
	int min_id = 0;
	int max_score = 0;
	int max_id = 0;
	for(i = 0; i < 10; i++)
	{
		sum = sum + students[i].score;
		if(students[i].score < min_score)
		{
			min_score = students[i].score;
			min_id = students[i].id;
		}
		if(students[i].score > max_score)
		{
			max_score = students[i].score;
			max_id = students[i].id;
		}
	}
	avg = sum / 10;
	

	printf("student with id %d", max_id);
	printf(" scored the highest with a score of %d\n", max_score);
	printf("student with id %d", min_id);
	printf(" scored the lowest with a score if %d\n", min_score);
	printf("the average score was: %d\n", avg);
	return;
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	free(stud);
	return; 
}

int main(){
    struct student* stud = NULL;
    
    /*call allocate*/
    stud = allocate();
    /*call generate*/
    generate(stud);
    /*call output*/
    output(stud);
    /*call summary*/
    summary(stud);
    /*call deallocate*/
    deallocate(stud);
    return 0;
}
