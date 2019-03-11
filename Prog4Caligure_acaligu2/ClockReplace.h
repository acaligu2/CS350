#ifndef CLOCK
#define CLOCK

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Clock{
	private:
		int blockSize;
		vector<pair<int, int> > cache;
		int numHits, numMisses;
		int currentIndex;
	public:
		Clock();
		double clockReplace(int, vector<int>);
		bool isFull();
		
};

#endif