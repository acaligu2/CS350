#include "Optimal.h"

double Optimal::optimalReplacement(int cacheSize, vector<int> pageAccesses){

	if(cacheSize == 0){ return 0; }

	int misses = 0;
	int hits = 0;

	int j = 0;

	for(int i = 0; i < pageAccesses.size(); i++){ 

		if(inCache(pageAccesses[i])){

			hits++;
			continue;
		}

		if(cache.size() < cacheSize){

			cache.push_back(pageAccesses[i]);

		}else{

			int j = replace(i + 1, pageAccesses);
			cache[j] = pageAccesses[i];

		}

	
	}
li
	misses = pageAccesses.size() - hits;

	double hitRate = (double) (hits) / (hits + misses);

	return hitRate;

}

bool Optimal::inCache(int val){

	if(find(cache.begin(), cache.end(), val) != cache.end()){ return true; }
	else{ return false; }

}

int Optimal::replace(int place, vector<int> pageAccesses){

	int x = 0;
	int farthest = place;

	for(int i = 0; i < cache.size(); i++){

		int j;
		for(int j = place; j < pageAccesses.size(); j++){

			if(cache[i] == pageAccesses[j]){

				if(j > farthest){

					farthest = j;
					x = i;

				}

				break;

			} 

		}


		if(j == pageAccesses.size()){ return i; }

	}


	return x;

	

}
