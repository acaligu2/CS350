#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv) {

	int numOfRand = 100;
	int minInt = 1;
	int maxInt = 255;
	char *output = NULL;
	unsigned long seed = time(0);

	int opt;
	while((opt = getopt(argc, argv, "un:m:M:s:o:")) != -1){
		switch(opt){

			case 'u':
				fprintf(stderr, "./prog1generator[-u] [-n <#ints>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file>]\n");
				exit(1);
			case 'n':
				numOfRand = atoi(optarg);
				if(numOfRand < 0 || numOfRand > 1000000){
					fprintf(stderr, "Error: Number of integers must be between 0 and 1,000,000");
					exit(1);
				} 
				break;
			case 'm':
				minInt = atoi(optarg);
				if(minInt < 1){
					fprintf(stderr, "Error: Minimum value must be at least 1");
					exit(1);
				}
				break;
			case 'M':
				maxInt = atoi(optarg);
				if(maxInt > 1000000){
					fprintf(stderr, "Error: Max value must be at most 1,000,000");
					exit(1);
				}
				if(maxInt < minInt){
					fprintf(stderr, "Error: Max value must be greater than minimum value");
					exit(1);
				}
				break;
			case 's':
				seed = strtoul(optarg, NULL, 0);
				break;
			case 'o':
				output = optarg;
				break;
			case '?':			
				fprintf(stderr, "./prog1generator[-u] [-n <#ints>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file>]\n");
				exit(1);
			case ':':
				fprintf(stderr, "./prog1generator[-u] [-n <#ints>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file>]\n");
				exit(1);
		}

	}

	int *array;
	array = (int *)malloc(sizeof(int)*numOfRand);
	if(array == NULL){

		perror("Error with array: ");
		exit(1);
	
	}

	srand(seed);

	if(output == NULL){ printf("%d\n", numOfRand); }

	int counter;
	for(counter = 0; counter < numOfRand; counter++){

		int random = minInt + rand() % (maxInt - minInt);

		array[counter] = random;

		if(output == NULL){ printf("%d\n", array[counter]); }

	}

	if(output != NULL){

		FILE *f;
		int i;

		f = fopen(output, "w");

		if(f == NULL){ perror("Error with file: "); exit(1); }

		fprintf(f, "%d\n", numOfRand);

		for(i = 0; i < numOfRand; i++){

			fprintf(f, "%d\n", array[i]);

		}

		fclose(f);

	}
	
	free(array);

	return 0;

}
