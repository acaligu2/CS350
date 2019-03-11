#ifndef RANDOM
#define RANDOM

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Random{
	private:
		int blockSize;
		vector<int> cache;
		int numHits, numMisses;
	public:
		Random();
		double randomReplace(int, vector<int>);
		bool isFull();
		//return function to get number of hits
};

#endif