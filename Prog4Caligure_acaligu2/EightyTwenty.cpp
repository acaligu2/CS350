#include "EightyTwenty.h"

EightyTwenty::EightyTwenty(){
	pageAccesses = vector<int> (10000);

	for(int i = 0; i < 10000; i++){
		int randomnum = rand() % 10;
		if(randomnum == 0 || randomnum == 1){
			pageAccesses[i] = rand() % 80 + 20;
		} else{
			pageAccesses[i] = rand() % 20;
		}
	}
}

vector<int> EightyTwenty::generateVector(){
	return pageAccesses;
}
