#ifndef VICTIM_DATA_STRUCTURES
#define VICTIM_DATA_STRUCTURES

#include <vector>

struct Point
{
	double x;
	double y;
};

std::vector<int> path;
std::vector<int> shortest_path;
std::vector<Point> points;

const int MAX_LOC = 12;
double mat[MAX_LOC][MAX_LOC];
int res[MAX_LOC];


#endif
