/**
* Project 2
* File: parent.c
* Authors: Edgar Cobos, Seth Merriss, Ivan Ruiz
*/

# include <stdio.h> 
# include <stdlib.h> 
# include <sys/types.h> 
# include <unistd.h> 
# include <time.h>
# include <ctype.h>

int aNumber(char * number){
	if(*number == '-'){ //check if negative number 
		number++; //if it is, then just move the pointer to the next char to allow neg val
	} 
	while(*number){ //dereference pointer to first char and eval until '\0' is reached
		if(!isdigit(*number)){ //dereference pointer to first char and eval
			return 0; //return false
		}
		number++; //move the pointer address to the next char
	}
	return 1; //return true
}

int main(int argc, char *argv[]) 
{ 
 	int a, b, sleeptime, seed; //create the argument variables
 	pid_t childpid; //create the PID variable
 	if (argc != 4) { 
 		printf("\n Usage: %s <sleeptime([1,50]> <int A> <int B>\n", argv[0]); 
	 	exit(1); 
	 } 
	
	//check to see if the arguments are digits
	if(!aNumber(argv[1]) || !aNumber(argv[2]) || !aNumber(argv[3]) ){
		printf("\n Please make sure to provide integers only\n Usage: %s <sleeptime[1,50]> <int A> <int B>\n", argv[0]);
		exit(1);
	}
	
	//get the arguments and assign them to local variables
 	sleeptime = atoi(argv[1]);
	a = atoi(argv[2]);
	b = atoi(argv[3]);
	
	if(sleeptime < 1 || sleeptime > 50){
		printf("\n Sleeptime must be between 1 and 50, inclusive.\n");
		exit(1);
	}
	
	if(b == 0){  //can't divide by zero, so we check for that possibility 
		printf("\n Error: Can't divide by zero.\n The third argument, B, may not be zero. \n");
		exit(1);
	}
	 
 	printf("I am parent process, the maximum sleep time is %d and the two numbers are %d and %d\n", sleeptime, a, b);
	
	srand((int)(getpid() + childpid)); //create the seed for the rand num generator
	sleeptime = rand() % sleeptime; //get a sleep time within range
	sleep(sleeptime); //put the process to sleep
	
	char operation[4]; //create the 'operation' buffer
 	for (int i=0; i < 4;i++){
		childpid = fork();
		if (childpid == 0){
			char pid[10]; //create the 'pid' buffer
			snprintf(pid, sizeof(pid), "%d", getpid()); //convert int to char array
			snprintf(operation, sizeof(1), "%d", i); //convert int to char array
			execlp("./child", "child", argv[1], argv[2], argv[3], pid , operation, (char *) NULL); 
			perror("\n Exec failure in parent\n");
			exit(1);
		} else if (childpid == -1) {  //check if there was a failure with forking
			perror("\n Fork failure\n");
			exit(1);
		}
		printf("Forked child %d\n", childpid);
	}		 
	 exit(0); 
} 
