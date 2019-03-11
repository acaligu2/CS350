#include "timer.h"

void setstart(){ gettimeofday(&start, NULL); }

void setend(){ gettimeofday(&end, NULL); timerFunc(); }

void timerFunc(){

	int val = (end.tv_sec - start.tv_sec);
	int val2 = (end.tv_usec - start.tv_usec);

	fprintf(stderr, "%d.%.6ld\n", val, val2);
	

}
