#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "toDoList.h"


int main (int argc, const char * argv[])
{
  char *cmd = malloc(100*sizeof(char));
  DynArr* mainList = createDynArr(10);
  
  
  
  printf("\n\n** TO-DO LIST APPLICATION **\n\n");

  do
    {
      printf("Press:\n"
             "'l' to load to-do list from a file\n"
             "'s' to save to-do list to a file\n"
             "'a' to add a new task\n"
             "'g' to get the first task\n"
             "'r' to remove the first task\n"
             "'p' to print the list\n"
             "'e' to exit the program\n"
             );
      /* get input command (from the keyboard) */
	  fgets(cmd, 10, stdin);
	  /* clear the trailing newline character */
	  if((strlen(cmd)>0) && (cmd[strlen (cmd) - 1] == '\n'))
        cmd[strlen (cmd) - 1] = '\0';

      /* Fixme:  Your logic goes here! */
	  FILE *tmp_file;
	  char *tmp_description = malloc(100*sizeof(char));
	  char *tmp_filename = malloc(100*sizeof(char));
      char *tmp_priority = malloc(100*sizeof(char));
      int is_number;
      int tmp_p;
      int i;
      char *ptr;
	  //Load List
	  if(cmd[0] == 'l')
	  {
		printf("\nPlease enter a filename: ");
		fgets(tmp_description, TASK_DESC_SIZE, stdin);
		if((strlen(tmp_description)>0) && (tmp_description[strlen (tmp_description) - 1] == '\n'))
        tmp_description[strlen (tmp_description) - 1] = '\0';
		sprintf(tmp_filename, tmp_description);
		
		tmp_file = fopen(tmp_filename, "r");
		loadList(mainList, tmp_file);
		fclose(tmp_file);
		printf("\nThe file %s has been loaded.\n\n", tmp_filename);
	  }
	  
	  //Save List
	  else if(cmd[0] == 's')
	  {
		printf("\nPlease enter a filename: ");
		fgets(tmp_description, TASK_DESC_SIZE, stdin);
		if((strlen(tmp_description)>0) && (tmp_description[strlen (tmp_description) - 1] == '\n'))
         tmp_description[strlen (tmp_description) - 1] = '\0';
		sprintf(tmp_filename, tmp_description);
		
		tmp_file = fopen(tmp_filename, "w");
		assert(tmp_file != 0);
		saveList(mainList, tmp_file);
		fclose(tmp_file);
		printf("\nThe file %s has been saved.\n\n", tmp_filename);
	  }
	  
	  //Add New Task
	  else if(cmd[0] == 'a')
	  {
		printf("\nPlease enter the task description: ");
		fgets(tmp_description, TASK_DESC_SIZE, stdin);
		if((strlen(tmp_description)>0) && (tmp_description[strlen(tmp_description) - 1] == '\n'))
        tmp_description[strlen (tmp_description) - 1] = '\0';
		is_number = 0;
		while(is_number == 0)
		{
			printf("\nPlease enter the task priority: ");
			fgets(tmp_priority, TASK_DESC_SIZE, stdin);
			if((strlen(tmp_priority)>0) && (tmp_priority[strlen(tmp_priority) - 1] == '\n'))
				tmp_priority[strlen (tmp_priority) - 1] = '\0';
			is_number = 1;
			if(!strlen(tmp_priority)) { is_number = 0;}
			for( i = 0; i < strlen(tmp_priority); i++)
			{
				if(!isdigit(tmp_priority[i]))
				{
					is_number = 0;
				}
			}
			if(!is_number) { printf("\nERROR: Invalid input, only positive integers allowed.\n");}
		}
		tmp_p = strtol(tmp_priority, &ptr, 10);
		
		addHeap(mainList, createTask(tmp_p, tmp_description), compare);
		printf("\nTask added.\n\n");
	  }
	  
	  //Get First Task
	  else if(cmd[0] == 'g')
	  {
		if(sizeDynArr(mainList))
		{
			printf("\nYour first ");
			print_type(getMinHeap(mainList));
			printf("\n\n");
		}
		else { printf("\nThe To-Do List is empty!\n\n");}
	  }
	  
	  //Remove First Task
	  else if(cmd[0] == 'r')
	  {
		if(sizeDynArr(mainList))
		{
			printf("\nYour first ");
			print_type(getMinHeap(mainList));
			printf(", has been removed from the list.\n\n");
			removeMinHeap(mainList, compare);
		}
		else { printf("\nThe To-Do List is empty!\n\n");}
		
	  }
	  
	  //Print List
	  else if(cmd[0] == 'p')
	  {
		if(sizeDynArr(mainList))
		{
			printf("\nPrinting List...\n\n");
			printList(mainList);
		}
		else { printf("\nThe To-Do List is empty!\n\n");}
	  }
	  
	  
      /* Note: We have provided functions called printList(), saveList() and loadList() for you
         to use.  They can be found in toDoList.c */
    }
  while(cmd[0] != 'e');
  /* delete the list */
  deleteDynArr(mainList);
  

  return 0;
}
