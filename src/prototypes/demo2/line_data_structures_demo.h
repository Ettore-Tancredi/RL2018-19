#ifndef LINE_DATA_STRUCTURES
#define LINE_DATA_STRUCTURES

#include <vector>

enum Colors
{
	WHITE,
	BLACK,
	GREEN,
	SILVER
};

struct Pixel
{
	int R;
	int G;
	int B;
};
using coord = std::pair<int, int>;

//join with Green_Cases?
enum Line_Cases
{
	NO_LINE = -1,
	STD_LINE,
	C_INTERSECTION,
	T_INTERSECTION,
	INTERRUPT,
	GREEN_R
};

enum Green_Cases
{
	G_LEFT = 0,
	G_RIGHT,
	G_BOTH
};

const int H = 400;
const int W = 400;
Pixel img[H][W];
int visited[H][W] = {};

std::vector<char>regions;
std::vector<coord>green_pixels;
int green_regions;

coord barycentre;
int nodes;
coord g_barycentre;
int g_nodes;

int instr[H*W+6] = {};
#endif // !DATA_STRUCTURES
