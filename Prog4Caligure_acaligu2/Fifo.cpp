#include "Fifo.h"

double Fifo::fifo(int cacheSize, vector<int> pageAccesses){

	if(cacheSize == 0){ return 0; }

	int misses = 0;
	int hits = 0;

	for(int i = 0; i < pageAccesses.size(); i++){ 

		if(cache.size() < cacheSize){

			if(cache.find(pageAccesses[i]) == cache.end()){

				cache.insert(pageAccesses[i]);

				misses++;

				indexes.push(pageAccesses[i]);
			
			}		

		}else{

			if(cache.find(pageAccesses[i]) == cache.end()){


				int temp = indexes.front();
				indexes.pop();
				cache.erase(temp);
				cache.insert(pageAccesses[i]);
				indexes.push(pageAccesses[i]);

				misses++;

			}

		}
	
	}

	hits = pageAccesses.size() - misses;

	double hitRate = (double) hits / (hits + misses);

	return hitRate;

}

bool Fifo::inCache(int val){

	if(cache.find(val) == cache.end()){ return true; }
	else{ return true; }

}
