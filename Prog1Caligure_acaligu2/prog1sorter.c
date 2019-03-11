#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "timer.h"

//Ask mike about argument parse shared code

int compare(const void * a, const void *b){
	
	return (*(int*)a - *(int*)b);
	
}

int main(int argc, char** argv){

	int numOfRand = 100;
	int argNumber = -1;
	int minInt = 1;
	int maxInt = 255;
	char *output = NULL;
	char *input = NULL;
	char *count = NULL;

	int opt;
	while((opt = getopt(argc, argv, "u:n:m:M:i:o:c:")) != -1){
		switch(opt){

			case 'u':
				fprintf(stderr, "./prog1sorter[-u] [-n <#ints>] [-m <min-int>] [-M <max-int>] [-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>]\n");
				exit(1);
			case 'n':
				argNumber = atoi(optarg);
				if(argNumber < 0 || argNumber > 1000000){
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
			case 'i':
				input = optarg;
				break;
			case 'o':
				output = optarg;
				break;
			case 'c':
				count = optarg;
				break;
		
			case '?':			
				fprintf(stderr, "./prog1sorter[-u] [-n <#ints>] [-m <min-int>] [-M <max-int>] [-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>]\n");
				exit(1);
			case ':':
				fprintf(stderr, "./prog1sorter[-u] [-n <#ints>] [-m <min-int>] [-M <max-int>] [-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>]\n");
				exit(1);

		}

	}

	setstart();

	int* inputArray;

	int inputNumber;
	
	if(input != NULL){
		int temp;
		int firstLine = 1;
		int counter = 0;
		FILE *file;
		file = fopen(input, "r");

		if(file == NULL){ perror("Error with file: "); exit(1); }
	
		while(fscanf(file, "%d\n", &temp) > 0 ){

			if(firstLine == 1){ 
				numOfRand = temp;
				firstLine = 0;
				if(argNumber != numOfRand && argNumber != -1 && !(argNumber > numOfRand)){

					fprintf(stderr, "Error: -n flag must equal first line of input\n");
					exit(1);

				}

				inputArray = (int *)malloc(sizeof(int)*numOfRand);
				if(inputArray == NULL){

					perror("Error with inputArray: ");
					exit(1);
	
				}		

			}else{

				if(counter > numOfRand){ break; }
				inputArray[counter] = temp;
				counter++;
			}
		
		
		}

		fclose(file);

	}else{
	
		int temp;
		int firstLine = 1;
		int counter = 0;		
		while(fscanf(stdin, "%d\n", &temp) > 0 ){	

			if(firstLine == 1){ 
				numOfRand = temp;
				firstLine = 0;
				if(argNumber != numOfRand && argNumber != -1){

					fprintf(stderr, "Error: -n flag must equal first line of input\n");
					exit(1);

				}

				inputArray = (int *)malloc(sizeof(int)*numOfRand);
				if(inputArray == NULL){

					perror("Error with inputArray: ");
					exit(1);
	
				}

			}else{

				if(counter >= numOfRand){ break; }
				inputArray[counter] = temp;
				counter++;
			}
		
		
		}		

	}


	int i;
	for(i = 0; i < numOfRand; i++){
		
		if(inputArray[i] < minInt || inputArray[i] > maxInt){ fprintf(stderr, "Error: At least one number was not in the specified range\n"); exit(1); }
		
	}
	
	qsort(inputArray, numOfRand, sizeof(int), compare);
	
	if(output == NULL){

		int j;
		for(j = 0; j < numOfRand; j++){
		
			printf("%d\n", inputArray[j]);
		
		}


	}else{

		FILE *f;
		int i;

		f = fopen(output, "w");

		if(f == NULL){ perror("Error with file: "); exit(1); }

		fprintf(f, "%d\n", numOfRand);

		for(i = 0; i < numOfRand; i++){

			fprintf(f, "%d\n", inputArray[i]);

		}

		fclose(f);

	}

	char *user;
	user = getenv("USER");

	if(count == NULL){

		int j;
		for(j = 0; j < strlen(user); j++){

			int i;
			int counter = 0;
			for(i = 0; i < numOfRand; i++){

				if(inputArray[i] == user[j]){ counter++; }

			}
	
			printf("%c\t%d\t%d\n", user[j], user[j], counter);
	
		}

	}else{

		FILE *f;
		int i;

		f = fopen(count, "w");

		if(f == NULL){ perror("Error with file: "); exit(1); }
		
		for(i = 0; i < strlen(user); i++){

			int j;
			int counter = 0;
			for(j = 0; j < numOfRand; j++){

				if(inputArray[j] == user[i]){ counter++; }

			}
	
			fprintf(f, "%c\t%d\t%d\n", user[i], user[i], counter);

		}

		fclose(f);

	}
	
	free(inputArray);

	setend();

	return 0;
	
}
