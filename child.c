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

int main(int argc, char *argv[]) { 
	 	int a, b, sleeptime, operation; 
	 	pid_t pid;

	 	if (argc != 6) { 
	 		printf("\n Usage: %s <sleeptime[1,50]> <int A> <int B> <PID> <operation>\n", argv[0]); 
		 	exit(1); 
		 } 
		
	 	sleeptime = atoi(argv[1]);
		a = atoi(argv[2]);
		b = atoi(argv[3]);
		pid = atoi(argv[4]);
		operation = atoi(argv[5]);
		
		if(b == 0){
			printf("\n Error: Can't divide by zero.\n The third argument, B, may not be zero. \n");
			exit(1);
		}
		
		srand((int)(getpid() + pid));
		sleeptime = rand() % sleeptime; 
		//printf("sleeping for %d... \n", sleeptime);
		sleep(sleeptime);
		
		switch (operation) {
			case 0:
				printf("I am child number %d with PID %d, the sum is %d\n", operation, pid, a+b );
				break;
			case 1:
				printf("I am child number %d with PID %d, the difference is %d\n", operation, pid, a-b );
				break;
			case 2:	
				printf("I am child number %d with PID %d, the quotient is %.2f and remainder is %d\n", operation, pid, (float)a/b, a%b);
				break;
			case 3:
				printf("I am child number %d with PID %d, the product is %d\n", operation, pid, a*b);
				break;
			default:
				break;
		}
		
		exit(0);
		
}
