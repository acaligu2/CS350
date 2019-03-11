#include <iostream>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h>
#include <list>
#include <algorithm>

using namespace std;

class LeastRecently{

	public:

		list<int> cache;
		unordered_map<int, list<int>::iterator> container;
		bool inCache(int val);
		double lru(int cacheSize, vector<int> pageAccesses);
	
};
