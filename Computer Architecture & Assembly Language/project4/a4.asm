	; Name: Mihai Dan
	; Creation date: 2/11/2015
	; Last modified: 2/13/2015 6:47pm
	;
	; 
	; Name of file: a4.asm
	; Description: 1. Reverse an array.
	;			   2. Rotate an array, left or right.
	;			   3. Frequency Table
	;			   4. Sieve of Eratosthenes
		
	; Assemble:	nasm -f elf -l a4.lst  a4.asm
	; Link:		gcc -m32 -o a4  a4.o -m32
	; Run:		./a4
	; Output:	

	; Equivalent C code
	;#include <stdlib.h>
	;#include <stdio.h>
	;
	;/*** Reverse an array in place ***/
	;int func1(int intArr[10]){
	;	//initialize  variables
	;	int start = 0, end = 9, eaxTemp, i;
	;	
	;	//print the initial array
	;	printf("Original Array: ");
	;	for(i = 0; i < 10; i++){
	;		printf("%d ", intArr[i]);
	;	}
	;	printf("\n");
	;	
	;	//flip the array in places
	;	for(i = 0; i < 5; i++){
	;		eaxTemp = intArr[start];
	;		intArr[start] = intArr[end];
	;		intArr[end] = eaxTemp;
	;		
	;		//increment start and decrement end
	;		start++;
	;		end--;
	;	}
	;	
	;	//print the flipped array
	;	printf("Reversed Array: ");
	;	for(i = 0; i < 10; i++){
	;		printf("%d ", intArr[i]);
	;	}
	;	printf("\n");
	;	//return intArray
	;	return *intArr;
	;}
	;
	;/*** Array Rotation ***/
	;int func2(int intArr[10]){
	;	//print the array
	;	int i;
	;	printf("Original Array: ");
	;	for(i = 0; i < 10; i++){
	;		printf("%d ", intArr[i]);
	;	}
	;	printf("\n");
	;	
	;	//decide between shifting left or right
	;	int val;
	;	printf("Would you like to rotate left or right? (1 - right; 0 - left)\n");
	;	scanf("%d", &val);
	;	
	;	int start = 0, end = 9, eaxTemp;
	;	//shift to the right
	;	if(val == 1){
	;		eaxTemp = intArr[end];
	;		for(i = 10; i >= 1; i--){
	;			intArr[i] = intArr[i-1];
	;		}
	;		intArr[start] = eaxTemp;
	;	}
	;	//shifts to the left
	;	if(val == 0){
	;		eaxTemp = intArr[start];
	;		for(i = 0; i <= 10; i++){
	;			intArr[i] = intArr[i+1];
	;		}
	;		intArr[end] = eaxTemp;
	;	}
	;	//prints the shifted array
	;	for(i = 0; i < 10; i++){
	;		printf("%d ", intArr[i]);
	;	}
	;	printf("\n");
	;	//return intArr
	;	return *intArr;
	;}
	;
	;/*** Frequency Table ***/
	;int func3(char stringArr[]){
	;	int countArr[128];
	;	int asciiArr[128];
	;	int num, i;
	;	
	;	//initialize countArr
	;	for(i = 0; i < 129; i++){
	;		countArr[i] = 0;
	;	}
	;	
	;	//initialize asciiArr
	;	for(i = 0; i < 129; i++){
	;		asciiArr[i] = 0;
	;	}
	;	
	;	//print the string
	;	printf("This is the string: '%s'\n", stringArr);
	;	
	;	//frequency
	;	for(i = 0; i < 30; i++){
	;		num = stringArr[i];
	;		printf("ASCII value = %d ", num);
	;		countArr[num]++;
	;		printf("Frequency: %d\n", countArr[i]); 
	;	}
	;}
	;
	;/*** Sieve of Eratosthenes ***/
	;int func4(){
	;	int limit, i, j;
	;
	;	//gets the limit for the Sieve of Eratosthenes
	;	printf("Please enter an integer: ");
	;	scanf("%d", &limit);
	;	
	;	//sieve array
	;	int sieve[limit];
	;	
	;	//fill the array from 1 to limit
	;	for(i = 0; i < limit; i++){
	;		sieve[i] = i+1;
	;	}
	;	
	;	//set 1 as a special
	;	sieve[0] = 0;
	;	
	;	//Sieve of Eratosthenes
	;	//seeds out the prime numbers
	;	for(i = 2; i < limit/2; i++){
	;		for(j = 1; j < limit; j++){
	;			if(sieve[j] != i && sieve[j]%i == 0){
	;				sieve[j] = 0;
	;			}
	;		}
	;	}
	;	
	;	//print out the prime numbers
	;	printf("Prime numbers: \n");
	;	for(i = 0; i < limit; i++){
	;		//filter the marked numbers
	;		if(sieve[i] != 0){
	;			printf("               %d\n", sieve[i]);
	;		}
	;	}
	;}
	;
	;
	;main(){
	;	int intArr[10];
	;	char stringArr[] = "This is a string for testing!";
	;	
	;	//fill the intArr array with numbers 0-9
	;	int i, fill, decision;
	;	for(i = 0; i < 10; i++){
	;		intArr[i] = fill+1;
	;		fill++;
	;	}
	;	
	;	//gives the user options
	;	printf("Welcome to Assignment 4 by Mihai Dan!\n");
	;	printf("Here are your options:\n");
	;	printf("1 - Reverse an array in place.\n");
	;	printf("2 - Rotate the array.\n");
	;	printf("3 - Construct a frequency table.\n");
	;	printf("4 - The Sieve of Eratosthenes.\n");
	;	printf("0 - Exit.\n");
	;	scanf("%d", &decision);
	;	
	;	if(decision == 0){
	;		printf("Good bye!\n");
	;	}
	;	if(decision == 1){
	;		func1(intArr);
	;	}
	;	if(decision == 2){
	;		func2(intArr);
	;	}
	;	if(decision == 3){
	;		func3(stringArr);
	;	}
	;	if(decision == 4){
	;		func4();
	;	}
	;}
	;
	; Declare needed external functions
	;
	extern	printf			; the C function, to be called
	extern  scanf 
SECTION .data				; Data section, initialized variables
	;introduction variables
	intro1: db "Hello! This is Assignment 4 by Mihai Dan!", 10, 0 	; printf format
	intro2: db "Please select one of the following: ", 10, 0
	intro3: db "1 - Reverse Array. 2 - Rotate Array. 3 - Frequency Table. 4 - Sieve of Eratosthenes.", 10, 0
	input: db "%d", 0
	userInput: dd 0
	counter: dd 0
	tester: db "TESTING TESTING TESTING", 10, 0
	here: db "HERE HERE HERE", 10, 0
	goodbye: db "Good bye! Have a beautiful time!", 10, 0
	template: db "TEST VAL: %d", 10, 0
	bad: db "Bad decisions were made...", 10, 0
	
	numArr: dd 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	arrLen: dd 10
	
	;reverse array function
	fmt: db "%d ", 0
	thing1: db "This is the array: ", 0
	thing2: db "This is the flipped array: ", 0
	endl: db "", 10, 0
	arrEnd: dd 10
	
	;rotate array function
	which: db "Rotate left(1) or right(2)?", 10, 0
	intake: db "%d", 0
	answer: dd 0
	thing3: db "This is the array shifted right: ", 10, 0
	thing4: db "This is the array shifted left: ", 10, 0
	scounter: dd 0
	eaxTemp: dd 0
	temp: dd 0
	
	;frequency table function
	string: dd 'aaaaa', 10, 0
	stringfmt: db "This is the string: '%s'", 0
	fcounter: dd 0
	count2: dd 0
	
	;Sieve function
	icounter: dd 2
	jcounter: dd 1
	pcounter: dd 0
	prime: dd 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20
	printfmt: db "%d ", 0
	
	


SECTION .bss				; BSS, uninitialized variables
	remainder: resd 1
	chararray: resd 128
	pval: resd 1
		
SECTION .text				; Code section.

	global main				; the standard gcc entry point

	main:					; the program label for the entry point
		push	ebp			; set up stack frame
		mov		ebp,esp
		
		;introduction with instructions on what to choose
		push dword intro1
		call printf
		push dword intro2
		call printf
		push dword intro3
		call printf
		add esp, 12
		
		;get input from user to make decision
		push dword userInput
		push dword input
		call scanf
		add esp, 8

		;if they choose 1, go to func1
		mov eax, [userInput]
		cmp eax, 1
		je .func1
		
		;if they choose 2, go to func2
		mov eax, [userInput]
		cmp eax, 2
		je .func2
		
		;if they choose 3, go to func3
		mov eax, [userInput]
		cmp eax, 3
		je .func3
		
		;if they choose 4, go to func4
		mov eax, [userInput]
		cmp eax, 4
		je .func4
		
		;if not, jump to last
		jmp .last
		
		;calls func1 then jumps to last
		.func1:
			call func1
			jmp .last
		
		;calls func2 then jumps to last
		.func2:
			call func2
			jmp .last

		;calls func3 then jumps to last
		.func3:
			call func3
			jmp .last

		;calls func4 then jumps to last
		.func4:
			call func4
			jmp .last
		
		;says goodbye
		.last:
			push dword goodbye
			call printf
			add esp, 4
			
			mov		esp, ebp	; takedown stack frame
			pop		ebp			; same as "leave" op

			mov		eax,0		; normal, no error, return value
			ret					; return
		
			
; *********** FUNC1 ************	
	func1:
		push	ebp			; set up stack frame
		mov		ebp,esp
		
		;introduce the original array
		push dword thing1	; thing1 is "this is the array:"
		call printf
		add esp, 4
		
		call arrPrint		; print the array
		
		mov esi, numArr		; move numArr into esi
		mov edi, numArr		; also move numArr into edi
		
		;set edi to the last value
		mov eax, [arrEnd]	; move the array end into eax
		mov ebx, 4			; mov 4 int ebx
		mul ebx				; eax * ebx
		add edi, eax		; move val of eax into edi
		
		mov ebx, 2			; move 2 into ebx
		mov eax, [arrLen]	; mov array length into eax
		cdq					; cdq
		div ebx				; eax / ebx
		
		mov [counter], eax	; mov eax into counter
		
		;reverse loop for array
		.loop:
			;decrement counter
			mov eax, [counter]
			dec eax
			mov [counter], eax
			
			;stack switch
			push dword [esi]	; push
			push dword [edi]	; push
			pop dword [esi]		; pop
			pop dword [edi]		; pop
			
			add esi, 4			; increment esi
			sub edi, 4			; decrement edi
			
			cmp eax, 0			; if counter is 0
			je .endfunc			; go to end func if equal
			
			cmp eax, 0			; if counter is 0
			jne .loop			; go to loop if not equal
	
		.endfunc:
			;prints the shifted array
			push dword thing2
			call printf
			add esp, 4
			
			call arrPrint		;print array
			
		mov		esp, ebp	; takedown stack frame
		pop		ebp			; same as "leave" op
		
		mov		eax,0		; normal, no error, return value
		ret					; return


		
; *********** FUNC2 *************
	func2:
		push	ebp			; set up stack frame
		mov		ebp,esp
		
		;introduce the array
		push dword thing1
		call printf
		add esp, 4
		
		;print array
		call arrPrint
		
		;ask user for left or right
		push dword which
		call printf
		add esp, 4
		
		;get user input into answer
		push dword answer
		push dword intake
		call scanf
		add esp, 8

		;if answer is 1, go to left
		mov eax, [answer]
		cmp eax, 1
		je .left
		
		;if answer is 2, go to right
		mov eax, [answer]
		cmp eax, 2
		je .right
		
		jmp .endfunc	;unconditional jump to end

		;shift to the right
		.right:
			;set counter to 10
			mov ecx, 10
			mov [scounter], ecx
			
			;save the last value into a temporary val
			mov eax, [numArr + 36]
			mov [temp], eax
			
			mov esi, numArr		; move numArr into esi
			mov edi, numArr		; move numArr into edi
			
			mov esi, [numArr + 36]	; sets esi to last val
			mov edi, [numArr + 32]	; sets edi to second to last val
			
			
			;set counter to 10
			mov ecx, 10
			mov [scounter], ecx
			mov eax, 9
			
			;right loop
			.loop:
				;decrement scounter 
				mov ecx, [scounter]
				dec ecx
				mov [scounter], ecx
				
				;move counter to eax
				mov eax, [scounter]
				
				;stack switch
				push edi	; push
				push esi	; push
				pop edi		; pop
				pop esi		; pop
				
				mov eax, [scounter]					; move counter to eax
				mov dword [numArr + 4*eax], esi		; save the value from esi into array
				dec eax								; decrement eax
				mov dword [numArr + 4*eax], edi		; save the value from edi into array
				
				mov eax, [scounter]					; mov scounter into eax
				sub eax, 1							; eax - 1
				
				mov dword esi, [numArr + 4*eax]		; next value into esi
				dec eax								; decrement eax
				mov dword edi, [numArr + 4*eax]		; next value into edi
				
				;if scounter is not equal to 0, repeat
				mov ecx, [scounter]
				cmp ecx, 0
				jne .loop
			
			;set the first value as temp
			mov eax, [temp]
			mov [numArr + 4], eax
			
			;print statement for shifted array
			push dword thing3
			call printf
			add esp, 4
			
			;unconditional jump
			jmp .endfunc

			
		.left:
			;set counter to 0
			mov ecx, 0
			mov [scounter], ecx
			
			;set the first value into a temp val
			mov eax, [numArr + 4]
			mov [temp], eax
			
			
			mov esi, numArr		; move numArr into esi
			mov edi, numArr		; move numArr into edi
			
			mov esi, [numArr + 4]	; first array val into esi
			mov edi, [numArr + 8]	; second array val into edi
			
			
			;set counter to 0
			mov ecx, 0
			mov [scounter], ecx
			mov eax, 0
			
			;loop for left
			.loop1:
				;increment the scounter
				mov ecx, [scounter]
				inc ecx
				mov [scounter], ecx
				
				;move the value of scounter into eax
				mov eax, [scounter]
				
				;stack switch
				push edi	; push
				push esi	; push
				pop edi		; pop
				pop esi		; pop
				
				;move scounter into eax
				mov eax, [scounter]
				
				mov dword[numArr + 4*eax], esi	; save val from esi in array
				inc eax							; increment eax
				mov dword [numArr + 4*eax], edi	; save val from edi in array
				
				;increment eax
				mov eax, [scounter]
				add eax, 1
				
				;sets esi and edi equal to the next value
				mov dword esi, [numArr + 4*eax]
				inc eax
				mov dword edi, [numArr + 4*eax]
				
				;if scounter is not 9, loop
				mov ecx, [scounter]
				cmp ecx, 9
				jne .loop1
			
			;set the last value as the temp from above
			mov eax, [temp]
			mov [numArr + 36], eax
			
			;print out the statement before array
			push dword thing3
			call printf
			add esp, 4
			
			;jump to end fucn
			jmp .endfunc
		
		.endfunc:
			call arrPrint
			
		mov		esp, ebp	; takedown stack frame
		pop		ebp			; same as "leave" op

		mov		eax,0		; normal, no error, return value
		ret					; return
		
		
		
;; *********** FUNC3 *************
	func3:
		push	ebp			; set up stack frame
		mov		ebp,esp
		
		push dword bad
		call printf
		add esp, 4
		
;	.zero:
;		mov eax, 0
;		jmp .originprint
;
;	.originprint:
;		push dword string
;		push dword stringfmt
;		call printf
;		add esp, 8
;		mov ecx, [count2]
;		mov ecx, 0
;		mov [count2], ecx
;
;	
;	.starts:
;		mov [counter], eax
;		mov edi, [counter]
;		add edi, string
;		mov al, [string]
;		jmp .incloop
;
;	.counts:
;		mov ecx, dword [chararray + eax]
;		inc ecx
;		mov dword [chararray + eax], ecx
;		mov ecx, 0
;		mov ecx, [chararray + eax]
;
;		push dword tester
;		call printf
;		add esp, 4
;
;		push dword ecx
;		push dword eax
;		call printf
;		add esp, 8
;
;		mov ecx, 0
;		jmp .starts
;
;	.incloop:
;		mov ecx, [count2]
;		inc ecx
;		mov [count2], ecx
;		cmp dword [count2], 7
;		jne .counts
;		jmp .end
;
;	.end:

		
	mov		esp, ebp	; takedown stack frame
	pop		ebp			; same as "leave" op

	mov		eax,0		; normal, no error, return value
	ret					; return
		
		
		
; *********** FUNC4 *************
	func4:
		push	ebp			; set up stack frame
		mov		ebp,esp
		
		push dword bad
		call printf
		add esp, 4
;		
;		.outerloop:
;			mov ebx, 2
;			mov eax, [icounter]
;			div ebx
;			
;			
;			mov [temp], edx
;			mov eax, [temp]
;			cmp eax, 0
;			je .innerloop
;			
;		.innerloop:
;			mov [jcounter], eax
;			mov eax, [jcounter]
;			inc eax
;			cmp eax, 20
;			je .check
;			
;			.check:
;				mov [temp], eax
;				push dword [temp]
;				push dword template
;				call printf
;				add esp, 8
;				
;				mov ebx, dword [prime + 4*eax]
;				cmp ebx, [icounter]
;				jne .setval
;			
;			
;		.setval:
;			mov eax, [jcounter]
;			mov ebx, 0
;			mov dword [prime + 4*eax], ebx
;			call print4
;			
;			mov eax, [icounter]
;			cmp eax, 10
;			je .ended
;			
;			jmp .outerloop
;
;		.ended:
;			mov		esp, ebp	; takedown stack frame
;			pop		ebp			; same as "leave" op
;
;			mov		eax,0		; normal, no error, return value
;			ret					; return
		
;	print4:			
;		push	ebp			; set up stack frame
;		mov		ebp,esp
		
;		mov eax, dword [prime + 4*ecx]
;		mov [pval], eax
;		
;		push dword [pval]
;		push dword printfmt
;		call printf
;		add esp, 8
		
		mov		esp, ebp	; takedown stack frame
		pop		ebp			; same as "leave" op

		mov		eax,0		; normal, no error, return value
		ret					; return
			
			

; *********** ARRAY PRINT ************	
	arrPrint:
		push	ebp			; set up stack frame
		mov		ebp,esp
		
		;set counter to zero
		mov eax, 0
		mov [counter], eax
		
		;print loop
		.printLoop:
			mov ebx, 0						; move ebx 0
			
			;increment counter
			mov eax, [counter]
			inc eax
			mov [counter], eax
			
			;print the val at the specific spot
			push dword [numArr + 4*eax]
			push dword fmt
			call printf
			add esp, 8
		
			;add 4 to ebx
			add ebx, 4
			
			;if counter equal to 9, jump to end line
			mov eax, [counter]
			cmp eax, 9
			je .endline
			
			;if not, loop
			mov eax, [counter]
			cmp eax, 9
			jne .printLoop
			
		
		.endline:
			;endline
			push dword endl
			call printf
			add esp, 4
			
		
		mov		esp, ebp	; takedown stack frame
		pop		ebp			; same as "leave" op
		
		mov		eax,0		; normal, no error, return value
		ret					; return