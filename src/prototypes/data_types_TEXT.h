#ifndef DATA_TYPES
#define DATA_TYPES

#include <vector>

enum Colors
{
	WHITE,
	BLACK,
	GREEN,
	SILVER
};
using coord = std::pair<int, int>;




const int H = 40;
const int W = 40;
char img[H][W];
int visited[H][W] = {};

std::vector<char>regions;
std::vector<coord>green_pixels;
int green_regions = 0;

coord barycentre;
int nodes;
coord g_barycentre;
int g_nodes;

std::string side;
std::string dir;

#endif // !DATA_TYPES