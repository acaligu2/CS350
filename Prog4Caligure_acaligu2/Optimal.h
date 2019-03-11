#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

class Optimal{

	public:

		vector<int> cache;
		bool inCache(int val);
		int replace(int i, vector<int> pageAccesses);
		double optimalReplacement(int cacheSize, vector<int> pageAccesses);
	
};
