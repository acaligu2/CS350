#include "NoLocality.h"

NoLocality::NoLocality(){
	pageAccesses = vector<int> (10000);
	for(int i = 0; i < 10000; i++){
		pageAccesses[i] = rand() % 100;
	}
}

vector<int> NoLocality::generateVector(){
	return pageAccesses;
}