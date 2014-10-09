# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>  

int main(int argc, char *argv[]) { 
	 	int a, b, sleeptime, operation; 
	 	pid_t pid;

	 	if (argc != 6) { 
	 		printf("\n Usage: %s <sleeptime(0,50)> <int A> <int B> <PID> <operation>\n", argv[0]); 
		 	exit(1); 
		 } 
		
	 	sleeptime = atoi(argv[1]);
		a = atoi(argv[2]);
		b = atoi(argv[3]);
		pid = atoi(argv[4]);
		operation = atoi(argv[5]);
		sleeptime = rand() % sleeptime; 
		sleep(sleeptime);
		switch (operation) {
			case 0:
				printf("I am child number %d with PID %d, the sum is %d\n", operation, pid, a+b );
				break;
			case 1:
				printf("I am child number %d with PID %d, the difference is %d\n", operation, pid, a-b );
				break;
			case 2:	
				printf("I am child number %d with PID %d, the quotient is %d and remainder is %d\n", operation, pid, a/b, a%b);
				break;
			case 3:
				printf("I am child number %d with PID %d, the product is %d\n", operation, pid, a*b);
				break;
			default:
				break;
		}
		
		exit(0);
		
}
