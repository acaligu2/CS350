#ifndef NONLOCAL
#define NONLOCAL

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class NoLocality{
	private:
		vector<int> pageAccesses;
	public:
		NoLocality();
		vector<int> generateVector();
};

#endif