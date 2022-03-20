#include <ctime>
#include "util.h"
using namespace std;
double time_cost()
{
	static clock_t prev_time=0;
	clock_t now=clock();
	double ret=(double) (now-prev_time) / CLOCKS_PER_SEC;
	prev_time=now;
	return ret;
}