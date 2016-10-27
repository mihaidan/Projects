/***************************************************
 * Name: Mihai Dan and Marc Ohlmann
 * File: calc.c
 * Date: 10/17/14
 * Assignment 2
 ***************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynamicArray.h"


/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num){
	char *end;
	double returnNum;
	
	returnNum = strtod(s, &end);
	
	/* If there's anything in end, it's not a number */
	if(strcmp(end, "") == 0){
		*num = returnNum;
		return 1;
	}else{
		return 0;
   }
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their sum is pushed back onto the stack.
*/
void add (struct DynArr *stack){
	/* FIXME: You will write this function */
	TYPE add1, add2;
	if(isEmptyDynArr(stack)==1){
		add1 = topDynArr(stack);
		popDynArr(stack);
		add2 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, add1 + add2);
	}
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack){
	/* FIXME: You will write this function */
	TYPE sub1, sub2;
	if(isEmptyDynArr(stack)==1){
		sub1 = topDynArr(stack);
		popDynArr(stack);
		sub2 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, sub1-sub2);
	}
}	


/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack){
	/* FIXME: You will write this function */
	TYPE div1, div2;
	if(isEmptyDynArr(stack)==1){
		div1 = topDynArr(stack);
		popDynArr(stack);
		div2 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, div1/div2);
	}
}

void product(struct DynArr *stack){
	TYPE multi1, multi2;
	if(isEmptyDynArr(stack) == 1){
		multi1 = topDynArr(stack);
		popDynArr(stack);
		multi2= topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, multi1*multi2);	
	}
}	

void square(struct DynArr *stack){
	TYPE square;
	if(isEmptyDynArr(stack) == 1){
		square = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, pow(square,2));	
	}
}

void power(struct DynArr *stack){
	TYPE temp1, temp2;
	if(isEmptyDynArr(stack) == 1){
		temp1 = topDynArr(stack);
		popDynArr(stack);
		temp2 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, pow(temp1,temp2));	
	}
}

void third(struct DynArr *stack){	
	TYPE cube;
	if(isEmptyDynArr(stack) == 1){
		cube = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, pow(cube,3));	
	}
}		

void absolute(struct DynArr *stack){
	TYPE abs;
	if(isEmptyDynArr(stack) == 1){
		abs = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, abs);	
	}
}

void root(struct DynArr *stack){
	TYPE sub1;
	if(isEmptyDynArr(stack) == 1){
		sub1 = topDynArr(stack);
		popDynArr(stack);
	}
}

void exponent(struct DynArr *stack){
	TYPE temp;
	if(isEmptyDynArr(stack) == 1){
		temp = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, exp(temp));	
	}
}

void nlogs(struct DynArr *stack){
	TYPE temp;
	if(isEmptyDynArr(stack) == 1){
		temp = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack,log(temp));	
	}
}

void logs(struct DynArr *stack){
	TYPE temp;
	if(isEmptyDynArr(stack) == 1){
		temp = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, log10(temp));	
	}
}

double calculate(int numInputTokens, char **inputString){
	int i;
	double result = 0.0;
	char *s;
	struct DynArr *stack;

	//set up the stack
	stack = createDynArr(20);
	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++){
		s = inputString[i];
		// Hint: General algorithm:
		// (1) Check if the string s is in the list of operators.
		//   (1a) If it is, perform corresponding operations.
		//   (1b) Otherwise, check if s is a number.
		//     (1b - I) If s is not a number, produce an error.
		//     (1b - II) If s is a number, push it onto the stack

	if(strcmp(s, "+") == 0){
		if(sizeDynArr(stack) >= 2){
			add(stack);
		}else{
			printf("Too many arguments");
			return 0;
		}
		printf("Adding\n");
		
	}else if(strcmp(s,"-") == 0){
		if(sizeDynArr(stack) >= 2){
			subtract(stack);
		}else{
			printf("Too many arguments");
			return 0;
		}
		printf("Subtracting\n");
		
	}else if(strcmp(s, "/") == 0){
		if(sizeDynArr(stack) >= 2){
			divide(stack);
		}else{
			printf("Too many arguments");
			return 0;
		}
		printf("Dividing\n");
		
		}else if(strcmp(s, "x") == 0){
			if(sizeDynArr(stack) >= 2){
				product(stack);
			}else{
				printf("Too many arguments");
				return 0;
			}
			printf("Multiplying\n");
			
		}else if(strcmp(s, "^") == 0){
			if(sizeDynArr(stack) >= 2){
				power(stack);
			}else{
				printf("Too many arguments");
				return 0;
			}
			printf("Power\n");
			
			}else if(strcmp(s, "^2") == 0){
				if(sizeDynArr(stack) >= 2){
					square(stack);	
				}else{
					printf("Too many arguments");
					return 0;
				}
			printf("Squaring\n");
		
		}else if(strcmp(s, "^3") == 0){
			if(sizeDynArr(stack) >= 2){
				third(stack);
			}else{
				printf("Too many arguments");
				return 0;
			}
			printf("Cubing\n");
		
		}else if(strcmp(s, "abs") == 0){
			if(sizeDynArr(stack) >= 2){
				absolute(stack);
			}else{
				printf("Too many arguments");
				return 0;	
			}
			printf("Absolute value\n");
		
		}else if(strcmp(s, "sqrt") == 0){
			if(sizeDynArr(stack) >= 2){
				root(stack);
			}else{
				printf("Too many arguments");
				return 0;
			}
			printf("Square root\n");
		
		}else if(strcmp(s, "exp") == 0){
			if(sizeDynArr(stack) >= 2){
				exponent(stack);
			}else{
				printf("Too many arguments");
				return 0;
			}
			printf("Exponential\n");
		
		}else if(strcmp(s, "ln") == 0){
			if(sizeDynArr(stack) >= 2){
				nlogs(stack);
			}else{
				printf("Too many arguments");
				return 0;
			}
			printf("Natural Log\n");
		
		}else if(strcmp(s, "log") == 0){
			if(sizeDynArr(stack) >= 2){
				logs(stack);
			}else{
				printf("Too many arguments");
				return 0;
			}
			printf("Log\n");	
		}else{
		// FIXME: You need to develop the code here (when s is not an operator)
		// Remember to deal with special values ("pi" and "e")
		double *num=0;
			if(strcmp(s,"e") == 0){
				pushDynArr(stack, 2.7182818);
			}else if(strcmp(s, "pi")){
				pushDynArr(stack, 3.14159265);
			}else if(isNumber(s,num)==1){
				pushDynArr(stack, *num);
			}else{
				printf("error, try again \n");
				return 0;
			}
		}
	}	
	/* FIXME: You will write this part of the function (2 steps below) 
	 * (1) Check if everything looks OK and produce an error if needed.
	 * (2) Store the final value in result and print it out.
	 */

	if(sizeDynArr(stack) == 1){
		result = topDynArr(stack);
		popDynArr(stack);
	
		printf("Equals: %lf",result);
		printf("\n");
		return result;
	}else{
		printf("error, please try again");
	}		
}

int main(int argc , char** argv){
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
	return 0;

	calculate(argc,argv);
	return 0;
}
 