/**
* Project 3
* file: child.c
* Authors: Edgar Cobos, Seth Merriss and Ivan Ruiz
*/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h> 
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

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

int main(int argc, char *argv[]) {
	
	char *file; //declare a pointer to a char array (string)
	int fileDesc; //declare the file descriptor
	int sleeptime;
	int n_try;
	int K;
	int count = 0; //declare and init the num try counter
	pid_t pid = getpid();
	srand((unsigned) pid); //set the random number seed
	
	if(argc != 5) {
			printf("\nUsage: %s <data file name> <number of tries> <sleep time> <K number>\n", argv[0]);
			exit(1);
	}
	
	file = "lock1"; //name the lock file
	n_try = atoi(argv[2]);
	sleeptime = atoi(argv[3]);
	K = atoi(argv[4]);
	
	//make sure that the sleeptime is within the proper range
	if(sleeptime < 0 ){
		printf("\nError: Sleeptime has to be a positive integers\n");
		exit(1);
	}
	
	//make sure that the num tries is within the proper raneg
	if(!aNumber(argv[2]) || n_try < 0){
		printf("\nError: Number of tries has to be a positive integer\n");
		exit(1);
	}
	
	++sleeptime; //increment sleeptime by one to make it inclusively the max sleeptime
	// creat success returns an int. Failure returns -1, sets errno
	while ((fileDesc = creat(file, 0)) == -1 && errno == EACCES) {
		//If there is a failure with creating the file, then 
		// increment the count of tries and place the process to sleep for period of time 
	 	if (++count < n_try) {
			int goSleep = rand() % sleeptime;
			//printf("\n--- PID: %d (k=%d), sleeping for: %d\n", pid, K, goSleep); //for debug
			sleep(goSleep); //place proc to sleep for a random time within range
			
		}
	 	else { 
			//if the file can't be created after the specified tries, the print out the error and exit out
			printf ("\n Unable to generate lock. k = %d\n", K); 
			kill(getpid(), K); 
	 	} 
	}
	 //deletes the descriptor from the per-process obj reference table
	close (fileDesc); 	
	//This only prints if the lock file was created succcessfully
	printf ("\n File %s has been created\n", file);
	
	//create a child process that will handle the printing of the specified file
	pid_t grandChild;
	if((grandChild = fork()) == 0){
		execlp("/bin/cat", "file print", argv[1], (char *) NULL);
		perror("\n Exec failure in the child\n");
		exit(1);
	}else if (grandChild == -1) {
		perror("\n Exec failure\n");
		exit(1);
	}
	
	unlink(file); //delete the lock file
	exit(pid & 255); //mask out the least significant 8 bits
}