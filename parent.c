# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h> 
# include <time.h>

int main(int argc, char *argv[]) 
{ 
 	int a, b, sleeptime, seed; 
 	pid_t childpid;
 	if (argc != 4) { 
 		printf("\n Usage: %s <sleeptime(0,50)> <int A> <int B>\n", argv[0]); 
	 	exit(1); 
	 } 
	
 	sleeptime = atoi(argv[1]);
	a = atoi(argv[2]);
	b = atoi(argv[3]);
	 
 	printf("I am parent process, the maximum sleep time is %d and the two numbers are %d and %d\n", sleeptime, a, b);
	sleeptime = rand() % sleeptime; 
	sleep(sleeptime);
	char operation[4]; //initialize the char
 	for (int i=0; i < 4;i++){
		childpid = fork();
		if (childpid == 0){
			char pid[10];
			snprintf(pid, sizeof(pid), "%d", getpid());
			snprintf(operation, sizeof(1), "%d", i);
			execlp("/Users/ecobos/git/cecs326/child", "child", argv[1], argv[2], argv[3], pid , operation, (char *) NULL); 
			perror("\nExec failure in parent\n");
			exit(1);
		} else if (childpid == -1) {
			perror("\nFork failure\n");
			exit(1);
		}
		printf("Forked child %d\n", childpid);
	}		 
	 exit(0); 
} 
