#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "Loop.h"
#include "EightyTwenty.h"
#include "NoLocality.h"
#include "Optimal.h"
#include "LeastRecently.h"
#include "Fifo.h"
#include "RandomReplace.h"
#include "ClockReplace.h"

using namespace std;

vector<int> noLocality;
vector<int> eightyTwenty;
vector<int> looping;

int main(int argc, char* argv[]){

	int memSize;
	string replacePolicy;
	string workload;

	Loop lvec = Loop();
	looping = lvec.generateVector();

	NoLocality nvec = NoLocality();
	noLocality = nvec.generateVector();

	EightyTwenty evec = EightyTwenty();
	eightyTwenty = evec.generateVector();

	
	Optimal o = Optimal();
	LeastRecently l = LeastRecently();
	Fifo f = Fifo();
	Random r = Random();
	Clock c = Clock();

	int opt;
	while((opt = getopt(argc, argv, "um:r:w:")) != -1){
		switch(opt){

			case 'u':
				fprintf(stderr, "./prog4swap[-u] [-m <memory-size>] [-r <replacement-policy>] [-w <workload>]\n");
				exit(1);
			case 'm':
				memSize = atoi(optarg);
				if(memSize < 5 || memSize > 100 || memSize % 5 != 0){
					fprintf(stderr, "Error: Memory size must be in 5 block increments between 5 and 100");
					exit(1);
				} 
				break;
			case 'r':
				replacePolicy = optarg;
				break;
			case 'w':
				workload = optarg;
				break;
			case '?':			
				fprintf(stderr, "./prog4swap[-u] [-m <memory-size>] [-r <replacement-policy>] [-w <workload>]\n");
				exit(1);
			case ':':
				fprintf(stderr, "./prog4swap[-u] [-m <memory-size>] [-r <replacement-policy>] [-w <workload>]\n");
				exit(1);
		}

	}
	
	double temp;

	if(workload == "Looping"){

		if(replacePolicy == "OPT"){ 
		
			if(memSize != 0) temp = o.optimalReplacement(memSize, looping) * 100;
			else temp = 0;

		}else if(replacePolicy == "LRU"){

			temp = l.lru(memSize, looping) * 100;

		}else if(replacePolicy == "FIFO"){

			temp = f.fifo(memSize, looping) * 100;

		}else if(replacePolicy == "Rand"){

			temp = r.randomReplace(memSize, looping) * 100;

		}else if(replacePolicy == "Clock"){

			temp = c.clockReplace(memSize, looping) * 100;

		}else{ cout << "Invalid Algorithm name" << endl; exit(1); }

	}else if(workload == "No-locality"){

		if(replacePolicy == "OPT"){ 
		
			if(memSize != 0) temp = o.optimalReplacement(memSize, noLocality) * 100;
			else temp = 0;

		}else if(replacePolicy == "LRU"){

			temp = l.lru(memSize, noLocality) * 100;

		}else if(replacePolicy == "FIFO"){

			temp = f.fifo(memSize, noLocality) * 100;

		}else if(replacePolicy == "Rand"){

			temp = r.randomReplace(memSize, noLocality) * 100;

		}else if(replacePolicy == "Clock"){

			temp = c.clockReplace(memSize, noLocality) * 100;

		}else{ cout << "Invalid Algorithm name" << endl; exit(1); }

	}else if(workload == "80-20"){

		if(replacePolicy == "OPT"){ 
		
			if(memSize != 0) temp = o.optimalReplacement(memSize, eightyTwenty) * 100;
			else temp = 0;

		}else if(replacePolicy == "LRU"){

			temp = l.lru(memSize, eightyTwenty) * 100;

		}else if(replacePolicy == "FIFO"){

			temp = f.fifo(memSize, eightyTwenty) * 100;

		}else if(replacePolicy == "Rand"){

			temp = r.randomReplace(memSize, eightyTwenty) * 100;

		}else if(replacePolicy == "Clock"){

			temp = c.clockReplace(memSize, eightyTwenty) * 100;

		}else{ cout << "Invalid Algorithm name" << endl; exit(1); }


	}else{ cout << "Invalid workload" << endl; exit(1); }

	if(temp > 99){ temp = 100.0; }

	char buf[20];
	sprintf(buf, "%f", temp);
	printf("%s", buf);
	
	return 0;

}
