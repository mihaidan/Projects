	; Name: Mihai Dan
	; Creation date: 2/2/2015
	; Last modified: 2/4/2015 9:03PM
	;
	; 
	; Name of file: fib.asm
	; Description: print out fib sequence up to 46 numbers, 5 per line, spaced out
		
	; Assemble:	nasm -f elf -l fib.lst  fib.asm
	; Link:		gcc -m32 -o fib  fib.o -m32
	; Run:		./fib
	; Output:	1     1     2     3     5
	;			8     13     21     34     55
	;           89     144     233     377     610
	; 			etc...

	; Equivalent C code
	;/*******************************************
	;Author: Mihai Dan
	;Course: CS 271-001
	;Instructor: Kevin McGrath
	;Date: 2/2/2015
	;Assignment: Assignment 3, Fibonacci Sequence
	;********************************************/
	;
	;#include <stdlib.h>
	;#include <stdio.h>
	;//set the constants MAX and MIN
	;const int MAX = 46;
	;const int MIN = 1;
	;
	;main(){
	;	char *username;
	;	int num;
	;	
	;	printf("This is the Fibonacci sequence program created by Mihai Dan!\n");
	;	
	;	username = (char *)malloc(sizeof(char)); //allocate memory
	;	printf("Please enter your name: \n");
	;	scanf("%s", &username); //get name from user
	;	
	;	printf("Welcome %s!\n", &username); //greet user
	;	
	;	do{
	;		printf("Please enter an integer in the range [1 ... 46]:");
	;		scanf("%d", &num);
	;	}while(num < MIN | num > MAX); //make sure number is between 1 and 46
	;	
	;	printf("This program will display the Fibonacci sequence from the up to the integer entered above.\n");
	;	printf("They will be 5 per line spaced apart.");
	;	
	;	int last = 0, holder = 0, print = 1;
	;	
	;	int i;
	;	for(i = 0; i < num; i++){
	;		if(i%5 == 0){
	;			printf("\n"); //makes a new line when there's 5 per line
	;		}
	;		printf("%d     ", print); //space out numbers
	;		
	;		//fib sequence
	;		holder = print;
	;		print = print + last;
	;		last = holder;
	;	}
	;	printf("\n");
	;}

	; Declare needed external functions
	;
	extern	printf			; the C function, to be called
	extern  scanf
SECTION .data				; Data section, initialized variables
	introduction: db "This is the Fibonacci sequence program created by Mihai Dan!", 10, 0 ;the printf format, "\n"
	get_username: db "Please enter your name: ", 10, 0 ;the printf format, "\n"
	get_user_name: db "%s", 0 ; scanf format
	welcome: db "Welcome %s!", 10, 0 ;the printf format, "\n"
	user_instructions: db "Please enter an integer in the range [1 ... 46]:", 10, 0
	get_user_data: db "%d", 0 ; scanf format
	rules: db "This program will display the Fibonacci sequence from the up to the integer entered above.", 10, 0
	rules1: db "They will be 5 per line spaced apart.", 10, 0
	space: db "%d     ", 0
	endl: db " ", 10, 0
	goodbye: db "Goodbye, %s!", 10, 0
	print: dd 1
	track: dd 0
	zero: dd 0
	one: dd 1
	second: dd 1
	four: dd 2
	five: dd 3
	printadd: dd 3
	lastadd: dd 2

SECTION .bss				; BSS, uninitialized variables
	username: resd 1
	num: resd 1
	last: resd 1
	holder: resd 1
		
SECTION .text				; Code section.

	global main				; the standard gcc entry point

	main:					; the program label for the entry point
		push	ebp			; set up stack frame
		mov		ebp,esp
		
		;introduction, asks for name
		push dword introduction						; pushes introduction
		push dword get_username						; pushes username
		call printf									; call to printf
		add esp, 8									; allocate memory
		
		;scanf the name from the user
		push dword username							; pushes username
		push dword get_user_name					; pushes get_user_name
		call scanf									; call to scanf
		add esp, 8									; allocate memory
		
		;welcomes the user by name
		push dword username
		push dword welcome
		call printf
		add esp, 8
		
		;prints instructions 
		push dword user_instructions
		call printf
		add esp, 4
		
		jmp .getInput								; jumps to .getInput	
		
		;gets input from the user
		.getInput:
			push dword num							; pushes num			
			push dword get_user_data				; pushes get_user_data
			call scanf								; scanf
			add esp, 8								; allocate memory
			
			mov eax, [num]							; moves value of num into eax
			cmp eax, 1								; compare eax to 1 
			jl .errorJump							; if less than, jump to errorJump
			cmp eax, 46								; compare eax t upper bound
			jg .errorJump							; if greaten than, jump to errorJump
			mov [num], eax							; move the value of eax into num
			jmp .zero								; jump unconditionally to zero
			
		;error check for previous function	
		.errorJump:
			mov eax, 0								; clear eax
			jmp .getInput							; jump to getInput
			
		;value zero function
		.zero:
			push dword [zero]				; prints out 0
			push dword space
			call printf
			add esp, 8
			
			mov ecx, 1						; move 1 int ecx
			mov [track], ecx				; move value from ecx into track
			mov ecx, 0						; clear out ecx
			
			mov eax, [num]					; move value of num into eax
			dec eax 						; decrement eax
			mov [num], eax					; move value of eax into num
			mov eax, 0						; clear eax
			jmp .desc						; jump to desc
			
			
		.desc:
			mov eax, [num]					; checks to see if loop is completed
			cmp eax, 0
			je .end							; jump to end
		
			mov eax, [print]				; move value of print into eax
			mov [holder], eax				; holder = print
			add eax, [last]					; print = print + last
			mov [print], eax				; value of eax put into print
			mov eax, [holder]				; value of holder put into eax
			mov [last], eax					; last = holder
			mov eax, 0						; clear eax
			mov eax, [print]				; move value of print into eax
			cmp eax, 1						; compare eax to 1
			je .firsttime					; jump to first time if they're equal

			mov [print], eax				; puts eax value into print
			mov eax, 0						; zeroes eax
			
			;check to see if program is over
			mov ecx, [num]					; move the value from num into ecx
			dec ecx							; decrement ecx
			cmp ecx, 0						; compare ecx to 0
			je .end							; jump to end if equal
		
			mov [num], ecx					; moves value in ecx into num
			mov ecx, 0						; clear ecx

			;increment track
			mov ecx, [track]				; move value of track into ecx
			inc ecx							; increment ecx
			mov [track], ecx				; move value from ecx into track
			mov ecx, 0						; clear ecx
			
			jmp .check						; jump to check
		
		;checks to see if there are 5 per line
		.check:
			mov ecx, [track]				; move track intro ecx
			cmp ecx, 5						; compare ecx and 5
			jle .printfunc					; jump to printfunc if less than equal to
			
			mov ecx, [track]				; moves track into ecx
			cmp ecx, 5						; compare ecx to 5
			jg .reset						; if greater then, jump to reset
		
		;assigns values to the first few print variables
		.firsttime:
			;check to see if program is over
			mov eax, [num]
			cmp eax, 0
			je .end
			
			;get eax value into num and clear eax
			mov [num], eax
			mov eax, 0
			
			;prints out a 1
			push dword [one]
			push dword space
			call printf
			add esp, 8
			
			;decrements num and clears eax
			mov eax, 0						; clear eax
			mov eax, [num]					; mov value of num into eax
			dec eax							; decrement eax
			mov [num], eax					; mov value of eax into num
			mov eax, 0						; clear eax

			;keep track of how many numbers displayed per line
			mov ecx, 0						; clear ecx
			mov ecx, [track]				; move value of track into ecx
			inc ecx							; increment ecx
			mov [track], ecx				; move value back into track
			mov ecx, 0						; clear ecx
			
			;check to see if program is over
			mov eax, [num]
			cmp eax, 0
			je .end
			
			;get eax value into num and clear eax
			mov [num], eax
			mov eax, 0
			
			;prints out the second 1
			push dword [one]
			push dword space
			call printf
			add esp, 8
			
			;keep track of how many numbers displayed per line
			mov ecx, [track]
			inc ecx
			mov [track], ecx
			mov ecx, 0
			
			;check to see if program is over
			mov eax, [num]
			cmp eax, 0
			je .end
			
			;get eax value into num and clear eax
			mov [num], eax
			mov eax, 0
			
			;decrements num and clears eax
			mov eax, 0
			mov eax, [num]
			dec eax
			mov [num], eax
			mov eax, 0

			;keep track of how many numbers displayed per line
			mov ecx, 0
			mov ecx, [track]
			inc ecx
			mov [track], ecx
			mov ecx, 0
			
			;prints out a 2
			mov eax, [second]
			mov [print], eax
			mov eax, 0
			cmp eax, 0

			;check to see if program is over
			mov eax, [num]
			cmp eax, 0
			je .end

			;decrements num and clears eax
			mov eax, 0
			mov eax, [num]
			dec eax
			mov [num], eax
			mov eax, 0

			; conditional jump to next
			mov eax, [num]						; move num value into eax
			cmp eax, 46							; if not equal to 46
			jne .next							; jump to next

		;prints out 4
		.next:
			;print out 4 and allocate memory
			push dword [four]
			push dword space
			call printf
			add esp, 8

			; checks to see if the program is over
			mov eax, [num]
			cmp eax, 0
			je .end

			jmp .secnext						; jump to second next

		;prints out 5
		.secnext:
			push dword [five]
			push dword space
			call printf
			add esp, 8

			;adds a new line
			push dword endl						; push endl
			call printf 						; call printf
			add esp, 4							; allocate memory

			;decrements eax and checks to see if program is over
			mov eax, [num]
			dec eax
			cmp eax, 0
			je .end

			cmp eax, 0							; compare eax to 0
			je .clears							; if equal, jump to clears

		;reassign values
		.clears:
			mov [num], eax						; move value of eax into num
			mov eax, 0							; clear eax

			;clears track to where it should be in sequence
			mov ecx, [track]
			mov ecx, 0
			mov [track], ecx

			;clears print to where it should be in sequence
			mov eax, [printadd]
			mov [print], eax
			mov eax, 0

			;clears last to where it should be in sequence
			mov eax, [lastadd]
			mov [last], eax
			mov eax, 0

			;checks if the program is over
			mov eax, [num]
			cmp eax, 0
			je .end

			mov [num], eax						; moves value from eax into num
			mov eax, 0							; clears eax
			jmp .desc							; jumps back to desc
			
		;printing function
		.printfunc:
			push dword [print]
			push dword space
			call printf
			add esp, 8
			jmp .desc
		
		;new line and reset track
		.reset:
			;prints a new line
			push dword endl
			call printf
			add esp, 4

			;prints the current value
			push dword [print]
			push dword space
			call printf
			add esp, 8
			
			;sets tracker back to one
			mov ecx, 1
			mov [track], ecx
			jmp .desc							; jumps back to desc
	
		.end:
			push dword endl						; new line
			call printf
			add esp, 4
			
			push dword username		; gets username
			push dword goodbye		; goodbye message
			call printf
			add esp, 8
			
			mov		esp, ebp	; takedown stack frame
			pop		ebp			; same as "leave" op

			mov		eax,0		; normal, no error, return value
			ret					; return
	