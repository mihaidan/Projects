	; Name: Mihai Dan
	; Creation date: 2/2/2015
	; Last modified: 2/4/2015 9:03PM
	;
	; 
	; Name of file: p2.asm
	; Description: Allow user to enter as many integers as they
	; 			   desire until a negative is entered. The # of
	;			   integers entered, sum, and average are displayed.
		
	; Assemble:	nasm -f elf -l p2.lst  p2.asm
	; Link:		gcc -m32 -o p2  p2.o -m32
	; Run:		./p2
	; Output:	Result:
	;			Number of non negative integers = x
	;			Sum = x
	;			Average = x
	;			Goodbye, user!

	; Equivalent C code
	;/*******************************************
	;Author: Mihai Dan
	;Course: CS 271-001
	;Instructor: Kevin McGrath
	;Date: 2/2/2015
	;Assignment: Assignment 3, Part 2
	;********************************************/
	;
	;#include <stdlib.h>
	;#include <stdio.h>
	;
	;int main(){
	;	char *username;
	;	
	;	printf("Hello! This is Part 2 of Assignment 3 by Mihai Dan!\n");
	;	
	;	username = (char *)malloc(sizeof(char));
	;	printf("Please enter your name: \n");
	;	scanf("%s", &username); //get name from user
	;	
	;	printf("Welcome, %s!\n", &username);
	;	//display instructions
	;	printf("This program will prompt you for a integer less than or equal to 100.\n");
	;	printf("To stop, you must enter a negative number.\n");
	;	printf("The program will display the number of non negative numbers, their sum, and average.\n");
	;	printf("Please begin entering numbers!\n");
	;	
	;	int num, dowhile = 1, numbers = 0, sum = 0;
	;	
	;	//allow user to put in as many numbers...
	;	do{
	;		scanf("%d", &num); //get input
	;		if(num < 0){ //...unless they enter a negative
	;			dowhile = 0;
	;			break;
	;		}
	;		if(num <= 100){
	;			numbers++; //increment
	;			sum = sum + num; //show sum
	;		}else{
	;			printf("Number over 100. Number must be less.\n");
	;		}
	;	}while(dowhile == 1);
	;	
	;	int av = sum/numbers; //average
	;	
	;	//final output
	;	printf("You entered a negative number! We're done!\n");
	;	printf("Results: \n Number of non negative integers = %d \n Sum = %d \n Average = %d\n", numbers, sum, av);
	;	printf("Goodbye, %s! \n", &username);
	;}

	; Declare needed external functions
	;
	extern	printf			; the C function, to be called
	extern  scanf
SECTION .data				; Data section, initialized variables
	upper: dd 100			; upper bound
	lower: dd 0				; lower bound
	intro: db "Hello! This is Part 2 of Assignment 3 by Mihai Dan!", 10, 0 	; printf format
	ask_username: db "Please enter your name: ", 10, 0 
	get_username: db "%s", 0
	welcome: db "Welcome, %s!", 10, 0
	desc1: db "This program will prompt you for a integer less than or equal to 100.", 10, 0
	desc2: db "To stop, you must enter a negative number.", 10, 0
	desc3: db "The program will display the number of non negative numbers, their sum, and average.", 10, 0
	desc4: db "Please begin entering numbers!", 10, 0
	get_num: db "%d", 0
	error_msg: db "Number over 100. Number must be less.", 10, 0
	results1: db "You entered a negative number! We're done!", 10, 0
	results2: db "Results:", 10, 0
	results3: db "Number of non negative integers = %d", 10, 0
	results4: db "Sum = %d", 10, 0
	results5: db "Average = %d", 10, 0
	spesh: db "No non negative integers were entered!", 10, 0
	goodbye: db "Goodbye, %s!", 10, 0
	num: dd 0
	sum: dd 0
	numbers: dd 0
	av: dd 0

SECTION .bss				; BSS, uninitialized variables
	username: resd 1		; variable for username
		
SECTION .text				; Code section.

	global main				; the standard gcc entry point

	main:					; the program label for the entry point
		push	ebp			; set up stack frame
		mov		ebp,esp
		
		;Displays the intro and asks the user to input their name
		push dword intro	; pushes intro
		push dword ask_username ; pushes ask_username
		call printf			; call to printf
		add esp, 8			; allocate memory
		
		;Get the name from the user and put it into username
		push dword username	; pushes username
		push dword get_username	; push get_username
		call scanf			; call to scanf
		add esp, 8			; allocate memory
		
		;Welcomes the user
		push dword username
		push dword welcome
		call printf
		add esp, 8
		
		;Displays the instructions for the user
		push dword desc1
		push dword desc2
		push dword desc3
		push dword desc4
		call printf
		add esp, 16
		
		;input funciton
		.input:
			;gets a number input by the user
			push dword num
			push dword get_num
			call scanf
			add esp, 8
			
			mov eax, [num]			; move num into eax
			cmp eax, [upper]		; compare eax and upper
			jg .errorMsg			; if num is greater, jump to errorMsg
			cmp eax, [lower]		; compare eax and lower
			jl .print				; if num is lower, jump to print
			
			jmp .func				; if it's fine, go to func
		
		.func:
			mov eax, [num]			; move num into eax
			add [sum], eax			; add eax to sum
			
			inc dword [numbers]		; increment numbers to keep track of how many
			
			
			jmp .input				; jump back to input, loop
		
		
		.errorMsg:
			push dword error_msg	; prints error message
			call printf
			add esp, 4
		
			jmp .input				; jump back to input, loop
			
			
		.print:
			;special case, if there are no numbers
			cmp dword [numbers], 0
			je .special				; jump to special
			
			push dword results1		; print the description of results
			push dword results2
			call printf
			add esp, 4
			
			push dword [numbers]	; prints how many non negative integers
			push dword results3
			call printf
			add esp, 8
			
			push dword [sum]		; prints the sum
			push dword results4
			call printf
			add esp, 8
			
			jmp .calcav				; jumps to calculate average
		
		;calculate the average
		.calcav:
			mov al, byte [sum]		; move sum to al
			xor ah,ah
			mov cl, [numbers]		; move number into cl
			div cl					; divide cl
			mov byte [av], al		; moves al into average
			
			jmp .finish				; jump to finish
			
		.finish:
			push dword [av]			; display the average
			push dword results5
			call printf
			add esp, 8
			
			push dword username		; gets the username
			push dword goodbye		; goodbye statement 
			call printf
			add esp, 8
			
			jmp .end				; jumps to end
			
		; special case function
		.special:
			push dword spesh		; print the special message
			push dword username		; gets username
			push dword goodbye		; goodbye message
			call printf
			add esp, 12
			
			jmp .end
			
		.end:
			mov		esp, ebp	; takedown stack frame
			pop		ebp			; same as "leave" op

			mov		eax,0		; normal, no error, return value
			ret					; return
	