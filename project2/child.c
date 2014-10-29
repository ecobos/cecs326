/**
* Project 2
* File: child.c
* Authors: Edgar Cobos, Seth Merriss, Ivan Ruiz
*/

# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <ctype.h>  

int aNumber(char * number){
	if(*number == '-'){ //check if negative number 
		number++; //if it is, then just move the pointer to the next char to allow neg val
	} 
	while(*number){ //dereference pointer to first char and eval until '\0' is reached
		if(!isdigit(*number)){ //dereference pointer to first char and eval
			return 0;
		}
		number++; //move the pointer address to the next char
	}
	return 1;
}

int main(int argc, char *argv[]) { 
	 	int a, b, sleeptime, operation; //create the argument variables
	 	pid_t pid; //create the PID variable

	 	if (argc != 6) { 
	 		printf("\n Usage: %s <sleeptime[1,50]> <int A> <int B> <PID> <operation>\n", argv[0]); 
		 	exit(1); 
		 } 
		
		//check to see if the arguments are digits
		if(!aNumber(argv[1]) || !aNumber(argv[2]) || !aNumber(argv[3]) || !aNumber(argv[4]) || !aNumber(argv[5]) ){
			printf("\n Please make sure to provide integers only\n"); 
			printf(" Usage: %s <sleeptime[1,50]> <int A> <int B> <PID> <operation>\n", argv[0]);
			exit(1);
		}
		
		//get the arguments and assign them to local variables
	 	sleeptime = atoi(argv[1]);
		a = atoi(argv[2]);
		b = atoi(argv[3]);
		pid = atoi(argv[4]);
		operation = atoi(argv[5]); //the specific operation to execute
		
		if(sleeptime < 1 || sleeptime > 50){
			printf("\n Sleeptime must be between 1 and 50, inclusive.\n");
			exit(1);
		}
		
		/*if(b == 0) { //can't divide by zero, so we check for that possibility 
			printf("\n Error: Can't divide by zero.\n The third argument, B, may not be zero. \n");
			exit(1);
		}*/
		
		srand((int)(getpid() + pid)); //create the seed for the random num generator
		sleeptime = rand() % sleeptime; //get a random sleeptime within range
		sleep(sleeptime); //place the process to sleep
		
		switch (operation) {
			case 0:
				printf("I am child number %d with PID %d, the sum is %d\n", operation, pid, a+b );
				break;
			case 1:
				printf("I am child number %d with PID %d, the difference is %d\n", operation, pid, a-b );
				break;
			case 2:	
				if(b == 0){
					printf("I am child number %d with PID %d, I can't divide by zero\n", operation, pid);
				}else{
					printf("I am child number %d with PID %d, the quotient is %d and remainder is %d\n", operation, pid, a/b, a%b);
				}
				break;
			case 3:
				printf("I am child number %d with PID %d, the product is %d\n", operation, pid, a*b);
				break;
			default:
				break;
		}
		
		exit(0);
		
}
