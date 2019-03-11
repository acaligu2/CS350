#include "ClockReplace.h"

Clock::Clock(){
	blockSize = 100;
	cache = vector<pair<int, int> > (100);
	numHits = 0;
	numMisses = 0;
	currentIndex = 0;

	for(int i = 0; i < cache.size(); i++){
		cache[i].first = -1;
		cache[i].second = 0;
	}

	
}

bool Clock::isFull(){
	bool full = true;
	for(int i = 0; i < cache.size(); i++){
		if(cache[i].first == -1) full = false;
	}
	return full;
}

double Clock::clockReplace(int memsize, vector<int> pageAccesses){
	blockSize = memsize;
	cache.resize(blockSize);

	for(int i = 0; i < pageAccesses.size(); i++){
		int inCache = 0;
		for(int j = 0; j < cache.size(); j++){
			if(pageAccesses[i] == cache[j].first){
				cache[j].second = 1;
				numHits++;
				inCache = 1;
			}
		}
		if(!inCache){
			numMisses++;
			while(cache[currentIndex].second != 0){
				cache[currentIndex++].second = 0;
				if(currentIndex == cache.size()) currentIndex = 0;
			}
			cache[currentIndex].first = pageAccesses[i];
			cache[currentIndex].second = 1;
		}
	}
	double hitRate = (double) numHits / (numHits + numMisses);
	return hitRate;
}

