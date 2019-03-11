#include "LeastRecently.h"


double LeastRecently::lru(int cacheSize, vector<int> pageAccesses){

	if(cacheSize == 0){ return 0; }

	int misses = 0;
	int hits = 0;

	for(int i = 0; i < pageAccesses.size(); i++){ 

		if(container.find(pageAccesses[i]) == container.end()){

			if(cache.size() == cacheSize){

				int last = cache.back();
				cache.pop_back();
				container.erase(last);				

			}

			misses++;

		}else{

			hits++;
			cache.erase(container[pageAccesses[i]]);

		}

		cache.push_front(pageAccesses[i]);
		container[pageAccesses[i]] = cache.begin();

		//Output the cache after each page access

		/*for(auto it = cache.begin(); it!= cache.end(); it++){

			cout << (*it) << " ";

		}
		cout << endl;*/

	}

	double hitRate = (double) hits / (hits + misses);

	return hitRate;

}

bool LeastRecently::inCache(int val){

	if(find(cache.begin(), cache.end(), val) != cache.end()){ return true; }
	else{ return false; }

}
