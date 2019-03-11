#include "Loop.h"

vector<int> Loop::generateVector(){

	int numOfPages = 10000;

	int j = 0;
	for(int i = 0; i < numOfPages; i++){

		loopPages.push_back(j);
		j++;
		if(j == 50){ j = 0; }
	
	}

	return loopPages;

}
