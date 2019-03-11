#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){

	int numLevels = 1;
	int numChildren = 1;
	int sleepTime = 1;
	bool pauseActive = false;
	bool sleepActive = false;
	int opt;
	while((opt = getopt(argc, argv, "uN:M:ps:")) != -1){
		switch(opt){

			case 'u':
				fprintf(stderr, "./Prog2tree[-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]\n");
				exit(1);
				
			case 'N':

				numLevels = atoi(optarg);
				if(numLevels > 4){

					fprintf(stderr, "Error: Level value must be at most 4\n");
					exit(1);

				}
				break;
				
			case 'M':

				numChildren = atoi(optarg);
				if(numChildren > 3){

					fprintf(stderr, "Error: Child value must be at most 3\n");
					exit(1);

				}
				break;
				
			case 'p':

				pauseActive = true;
				break;
				
			case 's':

				sleepTime = atoi(optarg);
				
				sleepActive = true;
				break;
				
			case '?':
				fprintf(stderr, "./Prog2tree[-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]\n");
				exit(1);			
				
			case ':':
				fprintf(stderr, "./Prog2tree[-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]\n");
				exit(1);

		}
		
	}
	
	if(pauseActive == true && sleepActive == true){
		
		fprintf(stderr, "Error: Cannot enable pause and sleep together\n");
		fprintf(stderr, "./Prog2tree[-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time>]\n");
		exit(1);
		
	}
	
	if(!pauseActive){ sleepActive = true; }
	
	printf("ALIVE: Level %d process with pid = %d, child of ppid = %d\n", numLevels, getpid(), getppid());
	fflush(stdout);
	
	int next = numLevels - 1;
	
	char arg1[20], arg2[20], arg3[20];
	snprintf(arg1, sizeof(arg1), "%d", next);
	snprintf(arg2, sizeof(arg2), "%d", numChildren);
	snprintf(arg3, sizeof(arg3), "%d", sleepTime);

	for(int i = 0; i < numChildren; i++){

		pid_t pid = fork();

		if(pid == -1){ perror("Error with fork()"); exit(1); }

		if(pid == 0){ 

			if(numLevels == 1 && sleepActive){
				
				sleep(sleepTime);
				
			}
			
			if(numLevels == 1 && pauseActive){
				
				pause();
				
			}

			if(next < 1){ return 0; }

			if(pauseActive){
				
		
				execlp("./prog2tree", "./prog2tree", "-N", arg1, "-M", arg2, "-p", NULL);

			}else{

			
				execlp("./prog2tree", "./prog2tree", "-N", arg1, "-M", arg2, "-s", arg3, NULL);	
			
			}
			
		}

	}
	
	for(int i = 0; i < numChildren; i++){
		
		wait(NULL);
		
	}
	
	printf("EXITING: Level %d process with pid = %d, child of ppid = %d\n", numLevels, getpid(), getppid());
	fflush(stdout);

	return 0;

}		
