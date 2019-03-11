#ifndef EIGHTYTWENTY
#define EIGHTYTWENTY

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class EightyTwenty{
	private:
		vector<int> pageAccesses;
	public:
		EightyTwenty();
		vector<int> generateVector();
};

#endif