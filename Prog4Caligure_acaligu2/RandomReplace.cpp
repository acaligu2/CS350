#include "RandomReplace.h"

Random::Random(){
	blockSize = 100;
	cache = vector<int> (100);
	numHits = 0;
	numMisses = 0;

	for(int i = 0; i < cache.size(); i++){
		cache[i] = -1;
	}
}

bool Random::isFull(){
	bool full = true;
	for(int i = 0; i < cache.size(); i++){
		if(cache[i] == -1) full = false;
	}
	return full;
}

double Random::randomReplace(int memsize, vector<int> pageAccesses){
	blockSize = memsize;
	cache.resize(blockSize);

	for(int i = 0; i < pageAccesses.size(); i++){
		int inCache = 0;
		for(int j = 0; j < cache.size(); j++){
			if(pageAccesses[i] == cache[j]){
				numHits++;
				inCache = 1;
			}
		}
		if(!inCache){
			numMisses++;
			if(!isFull()){
				int index = -1;
				for(int k = 0; k < cache.size(); k++){
					if(cache[k] == -1){
						if(index == -1){
							index = k;
						}
					}
				}
				cache[index] = pageAccesses[i];
			}
			else cache[rand() % blockSize] = pageAccesses[i];
		}
	}

	double hitRate = (double) numHits / (numHits + numMisses);
	return hitRate;
}

