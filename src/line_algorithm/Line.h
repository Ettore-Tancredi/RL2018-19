#ifndef LINE_H
#define LINE_H

#include <algorithm>
#include <vector>


using coord = std::pair<int, int>;

enum Line_Cases
{
	NO_LINE = -1,
	STD_LINE,
	C_INTERSECTION,
	T_INTERSECTION,
	INTERRUPT,
	GREEN_RIGHT,
	GREEN_LEFT,
	GREEN_BOTH
};

struct Line
{
    Line_Cases type;
    coord barycentre;
	int num_nodes=1;


	std::vector<coord> green_regions;
};




#endif