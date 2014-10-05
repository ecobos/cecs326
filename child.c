# include <stdio.h>
# include <time.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>  

int main(int argc, char *argv[]) { 
	 	int a, b, sleeptime; 
	 	pid_t pid;
	 
	 	if (argc != 5) { 
	 		printf("\n Usage: %s <sleeptime(0,50)> <int A> <int B> <PID>\n", argv[0]); 
		 	exit(1); 
		 } 
		
	 	sleeptime = atoi(argv[1]);
		a = atoi(argv[2]);
		b = atoi(argv[3]);
		pid = atoi(argv[4]);
		sleeptime = rand() % sleeptime; 
		sleep(sleeptime);
		printf("I am child number <blah> with PID %d\n", pid );
		exit(0);
		
}
