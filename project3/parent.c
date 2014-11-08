/**
* Project 3
* file: parent.c
* Authors: Edgar Cobos, Seth Merriss and Ivan Ruiz
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

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
	int status;
	pid_t pid, w; 
	char k_value[3];
			
	if(argc != 4) {
		printf("\nUsage: %s <data file name> <number of tries> <sleep time>\n", argv[0]);
		exit(1);
	}
	
	// find any lock files in the current dir and remove them
	char command[40];
	strcpy(command, "find . -name 'lock*' | xargs rm -f" ); 
	system(command);//Execute the unix command 
	
	int n_try = atoi(argv[2]);
	int sleeptime = atoi(argv[3]);	
	
	//make sure that the sleeptime and number of tries is a positive integer
	if(sleeptime < 1){
		printf("\nError: Sleeptime has to be a positive integers\n");
		exit(1);
	}
	
	//make sure that the num tries is within the proper range
	if(!aNumber(argv[2]) || n_try < 0){
		printf("\nError: Number of tries has to be a positive integers\n");
		exit(1);
	}
	
	//loop through to create 3 child processes
	for(int k = 0; k < 3; k++){
		if((pid = fork()) == 0){ //fork and enter if child process
			sprintf(k_value, "%d", k); //convert the int to a char *
			execlp("./child", "child process", argv[1], argv[2], argv[3], k_value, (char *) NULL);
			perror("\n Exec failure in parent\n"); //should only execute if an error occured with exec
			exit(1);
		} 
		else if (pid == -1){ //catch any forking failure
			perror("\n Fork failure\n");
			exit(1);
		}
		else printf ("Forked child %d\n", pid);
	}
	
	// Wait for children to complete and for its exit status
 	while ((w = wait(&status)) && w != -1) { 
		//wait for the process to return a status
 		if (w != - 1) printf ("Wait on PID %d returns status of: %04X\n", w, status); 
	} 
	exit(0);
}