	; Name: Mihai Dan
	; Creation date: 2/2/2015
	; Last modified: 2/4/2015 9:03PM
	;
	; 
	; Name of file: p3.asm
	; Description: Prints out 98765
		
	; Assemble:	nasm -f elf -l p3.lst  p3.asm
	; Link:		gcc -m32 -o p3  p3.o -m32
	; Run:		./p3
	; Output:	98765

	; Equivalent C code
	;/*******************************************
	;Author: Mihai Dan
	;Course: CS 271-001
	;Instructor: Kevin McGrath
	;Date: 2/2/2015
	;Assignment: Assignment 3, Part 3
	;********************************************/
	;
	;#include <stdio.h>
	;#include <stdlib.h>
	;
	;int main(){
	;	printf("Hello! This is Part 3 of Assignment 3 by Mihai Dan!\n");
	;	printf("This program will display integers 9 through 5!\n");
	;	
	;	int i;
	;	//loop that prints out 98765
	;	for(i = 9; i > 4; i--){
	;		printf("%d", i);
	;	}
	;	printf("\n");
	;}

	; Declare needed external functions
	;
	extern	printf			; the C function, to be called
SECTION .data				; Data section, initialized variables
	intro: db "Hello! This is Part 3 of Assignment 3 by Mihai Dan!", 10, 0 ;the printf format, "\n"
	desc: db "This program will display integers 9 through 5!", 10, 0 ;the printf format, "\n"
	print: db "%d", 0
	space: db " ", 10, 0
	val: dd 9

SECTION .bss				; BSS, uninitialized variables
		
SECTION .text				; Code section.

	global main				; the standard gcc entry point

	main:					; the program label for the entry point
		push	ebp			; set up stack frame
		mov		ebp,esp
		
		push dword intro	; print the intro
		call printf
		add esp, 4
		
		push dword desc		; print the description
		call printf
		add esp, 4
		
		.bigfunc:
			push dword [val]	; prints the value out
			push dword print
			call printf
			add esp, 8			; allocate spaces
			
			mov ecx, [val]		; move val into ecx
			dec ecx				; decrement ecx
			cmp ecx, 5			; compare 5 and ecx
			jl .end				; if less than, go to .end
			mov [val], ecx		; move ecx into val
			
			loop .bigfunc		; loop
			
		.end:
			push dword space	; print statement to end
			call printf
			add esp, 4
			
			mov		esp, ebp	; takedown stack frame
			pop		ebp			; same as "leave" op

			mov		eax,0		; normal, no error, return value
			ret					; return
	