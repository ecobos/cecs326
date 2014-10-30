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
			printf("\nUsage: %s <lock file name> <number of tries> <sleep time> <K number>\n", argv[0]);
			exit(1);
	}
	
	file = argv[1];
	sleeptime = atoi(argv[2]);
	n_try = atoi(argv[3]);
	K = atoi(argv[4]);
	
	if(sleeptime < 0 || n_try < 0){
		printf("\nError: Both sleeptime and number of tries have to be positive integers\n");
		exit(1);
	}
	
	// creat success returns an int. Failure returns -1, sets errno
	while ((fileDesc = creat(file, 0)) == -1 && errno == EACCES) {
		//If there is a failure with creating the file, then 
		// increment the count of tries and place the process to sleep for period of time 
	 	if (++count < n_try) 
			sleep(rand() % sleeptime); //place proc to sleep for a random time within range
	 	else { 
			//if the file can't be created after the specified tries, the print out the error and exit out
			printf ("\n Unable to generate. k = %d\n", K); 
			kill(getpid(), K); 
	 	} 
	}
	 //deletes the descriptor from the per-process obj reference table
	close (fileDesc); 	
	//This only prints if the lock file was created succcessfully
	printf ("\n File %s has been created\n", file);
	
	if(fork() == 0){
		execlp("/bin/cat", "file print", "text.dat", (char *) NULL);
		perror("\n Exec failure in the child\n");
		exit(1);
	}
	
	unlink(file); //delete the lock file
	exit(pid & 255); //mask out the least significant 8 bits
}