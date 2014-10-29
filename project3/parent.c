#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	
	int status;
	pid_t pid, w; 
	char k_value[3];
		
	if(argc != 4) {
		printf("\nUsage: %s <lock file name> <number of tries> <sleep time>\n", argv[0]);
		exit(1);
	}
	
	for(int k = 0; k < 3; k++){
		if((pid = fork()) == 0){
			sprintf(k_value, "%d", k);
			execlp("./child", "child process", argv[1], argv[2], argv[3], k_value, (char *) NULL);
			perror("\n Exec failure in parent\n");
			exit(1);
		} 
		else if (pid == -1){
			perror("\n Fork failure\n");
			exit(1);
		}
		else printf ("Forked child %d\n", pid);
	}
	
	/* Wait for children */ 
 	while ((w = wait(&status)) && w != -1) { 
		//wait for the process to return a status
 		if (w != - 1) printf ("Wait on PID: %d returns status of: %04X\n", w, status); 
	} 
	exit(0);
}