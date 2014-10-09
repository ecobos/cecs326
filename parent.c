# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h> 
# include <time.h>
# include <ctype.h>

int aNumber(char * number){
	while(*number){ //dereference pointer to first char and eval until '\0' is reached
		if(!isdigit(*number) && *number!='-'){ //dereference pointer to first char and eval
			return 0;
		}
		number++; //move the pointer address to the next char
	}
	return 1;
}

int main(int argc, char *argv[]) 
{ 
 	int a, b, sleeptime, seed; 
 	pid_t childpid;
 	if (argc != 4) { 
 		printf("\n Usage: %s <sleeptime(0,50)> <int A> <int B>\n", argv[0]); 
	 	exit(1); 
	 } 
	
	if(!aNumber(argv[1]) || !aNumber(argv[2]) || !aNumber(argv[3]) ){
		printf("\n Please make sure to provide integers only\n Usage: %s <sleeptime(0,50)> <int A> <int B>\n", argv[0]);
		exit(1);
	}
	
 	sleeptime = atoi(argv[1]);
	a = atoi(argv[2]);
	b = atoi(argv[3]);
	
	if(sleeptime < 1 || sleeptime > 50){
		printf("\n Sleeptime must be between 1 and 50, inclusive.\n");
		exit(1);
	}
	 
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
			execlp("./child", "child", argv[1], argv[2], argv[3], pid , operation, (char *) NULL); 
			perror("\n Exec failure in parent\n");
			exit(1);
		} else if (childpid == -1) {
			perror("\n Fork failure\n");
			exit(1);
		}
		printf("Forked child %d\n", childpid);
	}		 
	 exit(0); 
} 
