
	; Name: Mihai Dan
	; Creation date: 22 January 2015
	; Last modified: 09:09 22 January 2015
	;
	; 
	; Name of file: hmwk2.asm
	; Description: This program is a simply calculator, calculating addition, subtraction, multiplication, and division of two numbers.
		
	; Assemble:	nasm -f elf -l hmwk2.lst  hmwk2.asm
	; Link:		gcc -o hmwk2  hmwk.o
	; Run:		hmwk2
	; Output:	The program will output the result to the addition, subtraction, multiplication, and division of the two numbers provided.

	; Equivalent C code
	;#include <stdio.h>
	;#include <stdlib.h>
	;#include <math.h>
	;
	;int main(){
	;	int firstn, secondn;
	;	
	;	printf("Hello! Welcome to Mihai's simple calculator!\n");
	;	
	;	printf("Please enter two numbers you would like calculated, separated by a space (ex. 1 2):\n");
	;	scanf("%d %d", &firstn, &secondn);
	;		
	;	printf("You entered %d and %d.\n", firstn, secondn);
	;		
	;	int adds = firstn + secondn;
	;	int subs = firstn - secondn;
	;	int muls = firstn * secondn;
	;	int divs = firstn / secondn; //typecast to floats to allow decimals
	;	int remainder = firstn % secondn
	;
	;	printf("The result to the addition is %d\n", adds); 
	;	printf("The result to the subtraction is %d\n", subs); 
	;	printf("The result to the multiplication is %d\n", muls); 
	;	printf("The result to the division is %d with remainder %d", divs, remainder); //gives three decimal points for extra credit
	;			
	;			
	;	printf("The second number is greater than the first. This is not allowed for extra credit.\n");
	;	printf("Would you like to retry? (1 = y, 0 = n)");
	;	scanf("%d", &retry);
	;	
	;	printf("Have a wonderful day. Goodbye!");
	;	
	;}

	; Declare needed external functions
	;
		extern	printf			; C print function
		extern  scanf           ; C input function
SECTION .data				; Data section, initialized 
	fmt1: db "Hello! Welcome to Mihai's simple calculator!", 10 ;the printf format, "\n"
	fmt2: db "Please enter two numbers you would like calculated, separated by a space (ex. 1 2):", 10 ; the printf format, "\n"
	input1: db "%d %d", 0 ; scanf format
	output1: db "The result to the addition is %d", 10, 0 ; the printf format, "\n", 0 
	output2: db "The result to the subtraction is %d", 10, 0 ; the printf format, "\n", 0 
	output3: db "The result to the multiplication is %d", 10, 0 ; the printf format, "\n", 0 
	output4: db "The result to the division is %d with remainder %d", 10, 0 ; the printf format, "\n", 0 
	fmt3: db "Have a wonderful day. Goodbye!", 10 ; printf format, "\n"

SECTION .bss				; BSS, uninitialized variables
	firstn: resd 1
	secondn: resd 1
	adds: resd 1
	subs: resd 1
	muls: resd 1
	divs: resd 1
	remainder: resd 1
		
SECTION .text				; Code section.

	global main				; the standard gcc entry point

	main:					; the program label for the entry point
		push	ebp			; set up stack frame
		mov		ebp,esp
		
		push dword fmt1
		call printf
		add esp, 4
		
		push dword fmt2
		call printf
		add esp, 4
		
		push dword secondn
		push dword firstn
		push dword input1
		call scanf
		add esp, 12
		
		mov eax, [firstn]			; puts firstn into eax
		add dword [secondn], eax	; eax = eax + secondn
		mov [adds], eax				; takes the value from eax and puts it int adds
		
		mov eax, [firstn]			; puts firstn into eax
		sub dword [secondn], eax	; eax = eax - secondn
		mov [subs], eax				; takes the value from eax and puts it int subs
		
		mov eax, [firstn]			; puts firstn into eax
		mul dword [secondn]			; eax = eax * secondn
		mov [muls], eax				; takes the value from eax and puts it int muls	
		
		mov eax, [firstn]			; puts firstn into eax
		div dword [secondn]			; eax = eax / secondn
		mov [divs], eax				; takes the value from eax and puts it int divs
		mov [remainder], edx		; gets the remainder
		
		push dword [remainder]
		push dword [divs]
		push dword output4
		call printf
		add esp, 12
		
		push dword [muls]
		push dword output3
		call printf
		add esp, 8
		
		push dword [subs]
		push dword output2
		call printf
		add esp, 8
		
		push dword [adds]
		push dword output1
		call printf
		add esp, 8

		mov		esp, ebp	; takedown stack frame
		pop		ebp			; same as "leave" op

		mov		eax,0		; normal, no error, return value
		ret					; return
	