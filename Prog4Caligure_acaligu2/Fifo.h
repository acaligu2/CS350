#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Fifo{

	public:

		unordered_set<int> cache;
		queue<int> indexes;

		bool inCache(int val);
		double fifo(int cacheSize, vector<int> pageAccesses);
	
};
