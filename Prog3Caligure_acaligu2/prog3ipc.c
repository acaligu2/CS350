#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int LevelNumber = 0;

void signalHandler(int sig){

	exit(0);

}

void childFunc(){

	//printf("Inside child function for pid: %d\n", getpid());
	signal(SIGUSR1, signalHandler);
	pause();

}

int main(int argc, char** argv){

	int numProcesses;
	int counter = 0;
	
	//Process command arguments
	/*-----------------------------------------------------------------*/
	if(argc != 2){

		fprintf(stderr, "Error: Must Specify Number of Processes\n");
		fprintf(stderr, "./prog3ipc <num-procs>\n");
		exit(1);

	}else{

		int temp = atoi(argv[1]);
		if(temp < 1 || temp > 32){

			fprintf(stderr, "Error: Process number must be between 1 and 32\n");
			exit(1);

		}else{

			numProcesses = temp;

		}

	}

	LevelNumber = numProcesses - 1;

	//creating shared memory
	/*-----------------------------------------------------------------*/

	int arr[numProcesses];
	const int SIZE = sizeof(arr);
	const char* name = "SM";
	const char message = getpid();
	
	int shm_fd;
	void *ptr;
	
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);

	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	int *iptr = (int *)ptr;

	//creating named pipe
	/*-----------------------------------------------------------------*/
	int fd;
	char * acaligu2 = "/tmp/acaligu2";
	char buf[1024];
	mkfifo(acaligu2, 0666);	


	//creating ordinary pipe
	/*-----------------------------------------------------------------*/

	int pfds[2];
	int sentVal = 0;
	int receivedVal = numProcesses;

	//Begin forking processes
	/*-----------------------------------------------------------------*/
	int i;
	for(i = 0; i < numProcesses; i++){

		printf("ALIVE: Level %d process with pid = %d, child of ppid = %d\n", receivedVal, getpid(), getppid());
		fflush(stdout);

		pipe(pfds);
	
		pid_t pid = fork();

		if(pid < 0){

			fprintf(stderr, "Failure with fork()\n");
			exit(1);

		}

		//Child
		if (pid == 0){

			//Add pid to the array
			iptr[counter] = getppid();
			counter++;

			//Read from the unnamed pipe
			close(pfds[1]);

			read(pfds[0], &receivedVal, sizeof(int));

			close(pfds[0]);

			//Check if this is the last child, then write to the named pipe and send to 				the wait
			if(receivedVal == 1){

				printf("ALIVE: Level %d process with pid = %d, child of ppid = %d\n", receivedVal, getpid(), getppid());
				fflush(stdout);

				iptr[counter] = getpid();
	
				fd = open(acaligu2, O_WRONLY);
			
				if(fd < 0){

					perror("Opening Write of Named Pipe Error\n"); exit(1);

				}else{

					int num = write(fd, "Y", sizeof("Y"));
					if(num < 0){ perror("Writing to Named"); exit(1); }

					close(fd);
	
					childFunc();

				}

			}

		
		//Parent
		}else{

			//Add PID to array
			iptr[counter] = getpid();
			counter++;

			//Write to unnamed pipe
			close(pfds[0]);

			int sentVal = receivedVal - 1;
		
			write(pfds[1], &sentVal, sizeof(int));
		
			close(pfds[1]);

			
			//If not the top level, send to pause()
			if(counter != 1){

                            	childFunc();
 
			//Otherwise setup the Named Pipe to read from last child
                        }else{

				counter++;
				fd = open(acaligu2, O_RDONLY);
				if(fd < 0){

					perror("Opening Read of Named Pipe Error\n"); exit(1);

				}else{
					
					int num = read(fd, buf, 1024);

					if(num < 0){
					
						perror("Named Pipe Error\n");
						exit(1);

					}else{

						close(fd);

						for(i = 0; i < numProcesses; i++){
	 
							printf("%d\n", iptr[i]);
						
						}

						int j = numProcesses - 1;
						for(i = 1; i < numProcesses; i++){

							//I was having a tough time getting a global variable to represent the level of the process while in the signal handler so I had to put the exits just before the kill() and reference the pid() using the shared memory.
	 					

							printf("EXITING: Level %d process with pid = %d, child of ppid = %d\n", j, iptr[i], iptr[i-1]);
							fflush(stdout);
							j--;
							kill(iptr[i], SIGUSR1);
							

						}

					}

				}

			}

			break;
			
		}

	}

	unlink(acaligu2);
	shm_unlink(name);

	sleep(.25);

	printf("EXITING: Level %d process with pid = %d, child of ppid = %d\n", numProcesses, getpid(), getppid());
	fflush(stdout);

	return 0;
}
