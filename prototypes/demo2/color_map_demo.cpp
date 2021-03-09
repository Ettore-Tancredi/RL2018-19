#include <iostream>
#include <fstream>
#include <stack>
#include <utility>
#include <string>
#include "pixel_demo.h"
#include <chrono>
#include <cmath>


/****************************************************************************************
void df(start i_coordinate, start j_coordinate, region number, validation criteria)
	- Beginning from the start pixel, it explores all adjacent pixels that satisfy the
		input criteria (i.e. the desired color) and that haven't been visited yet.
	- While exploring, it marks all the pixels it finds with the region number at the
		corrisponding indexes	in the "visited" matrix.
	- It ends once it can no longer find acceptable pixels.
***********************************************************************************/
void dfs(int i, int j, int isl, int target)
{
	std::stack<coord> stack;
	stack.push(std::make_pair(i, j));

	while (!stack.empty())
	{
		if (visited[stack.top().first][stack.top().second] > 0)
		{
			stack.pop();
		}
		else
		{
			int i = stack.top().first;
			int j = stack.top().second;
			for (int c = -1; c < 2; ++c)
				for (int t = -1; t < 2; ++t)
					if (pixel::isInside(i + c, j + t) && !(c == 0 && t == 0))
					{
						if (pixel::isValid(i + c, j + t, target) && (visited[i + c][j + t] == 0) && (pixel::color(i + c, j + t) == target))
							stack.push(std::make_pair(i + c, j + t));

						//look for green pixels adjacent to the borders of the black line
						if (pixel::color(i + c, j + t) == GREEN && target == BLACK)
							green_pixels.push_back(std::make_pair(i + c, j + t));
					}

			if (target == BLACK)
			{
				barycentre.first += i;
				barycentre.second += j;
				++nodes;
			}
			else if (target == GREEN)
			{
				g_barycentre.first += i;
				g_barycentre.second += j;
				++g_nodes;
			}
			visited[i][j] = isl;
		}
	}
}


//UTILTY FUNCTIONS
bool find_region(char region)
{
	for (int i = 0; i < regions.size(); ++i)
		if (regions[i] == region)
			return true;
}
int count_regions(char region)
{
	int num = 0;
	for (int i = 0; i < regions.size(); ++i)
		if (regions[i] == region)
			++num;
	return num;
}


//PYTHON INTERFACE
/*****************************************************
int* load_image(image RGB matrix, height, width)
	- copies the input image into the gloabal variable.
	- resets all the global variable for the new frame
	- launches a dfs each time it finds an univisited black
		pixel along the borders.
	- Decides which strategy to apply based on the collected
		data.
	- returns the visited[][] matrix as an array and appends
		the strategy instructions
*****************************************************/

extern "C" int* load_image(int arr[400][400][4], int H, int W)
{
	for (int i = 0; i < H; ++i)
	{
		for (int j = 0; j < W; ++j)
		{
			img[i][j].R = arr[i][j][0];
			img[i][j].G = arr[i][j][1];
			img[i][j].B = arr[i][j][2];
			visited[i][j] = 0;
		}
	}



	barycentre.first = 0;
	barycentre.second = 0;
	nodes = 1;

	g_barycentre.first = 0;
	g_barycentre.second = 0;
	g_nodes = 0;
	green_regions = 0;

	while (green_pixels.size() > 0)
		green_pixels.pop_back();
	while (regions.size() > 0)
		regions.pop_back();

//BOTTOM
	for (int i = 0; i < W; ++i)
	{
		if (pixel::color(H - 1, i) == BLACK)
		{
			if (visited[H - 1][i] == 0)
			{
				dfs(H - 1, i, regions.size() + 1, BLACK);
				regions.push_back('B');
			}

			if (pixel::color(H - 1, i - 1) == WHITE && visited[H - 1][i - 1] == 0)
			{
				dfs(H - 1, i - 1, regions.size() + 1, WHITE);
				regions.push_back('W');
			}

			while (pixel::color(H - 1, i) == BLACK)
				++i;

			if (pixel::color(H - 1, i + 1) == WHITE && visited[H - 1][i + 1] == 0)
			{
				dfs(H - 1, i + 1, regions.size() + 1, WHITE);
				regions.push_back('W');
			}
		}

	}

//LEFT
	for (int i = 0; i < H - 1; ++i)
	{

		if (pixel::color(i, W - 1) == BLACK)
		{
			if (pixel::color(i - 1, W - 1) == WHITE && visited[i - 1][W - 1] == 0)
			{
				dfs(i - 1, W - 1, regions.size() + 1, WHITE);
				regions.push_back('W');
			}

			while (pixel::color(i, W - 1) == BLACK)
				++i;

			if (pixel::color(i + 1, W - 1) == WHITE && visited[i + 1][W - 1] == 0)
			{
				dfs(i + 1, W - 1, regions.size() + 1, WHITE);
				regions.push_back('W');
			}
		}
	}

//UP
	for (int i = 0; i < W; ++i)
	{
		if (pixel::color(0, i) == BLACK)
		{
			if (pixel::color(0, i - 1) == WHITE && visited[0][i - 1] == 0)
			{
				dfs(0, i - 1, regions.size() + 1, WHITE);
				regions.push_back('W');
			}

			while (pixel::color(0, i) == BLACK)
				++i;

			if (pixel::color(0, i + 1) == WHITE && visited[0][i + 1] == 0)
			{
				dfs(0, i + 1, regions.size() + 1, WHITE);
				regions.push_back('W');
			}
		}
	}

//RIGHT
	for (int i = 0; i < H; ++i)
	{
		if (pixel::color(i, 0) == BLACK)
		{
			if (pixel::color(i - 1, 0) == WHITE && visited[i - 1][0] == 0)
			{
				dfs(i - 1, 0, regions.size() + 1, WHITE);
				regions.push_back('W');
			}

			while (pixel::color(i, 0) == BLACK)
				++i;

			if (pixel::color(i + 1, 0) == WHITE && visited[i + 1][0] == 0)
			{
				dfs(i + 1, 0, regions.size() + 1, WHITE);
				regions.push_back('W');
			}
		}
	}

//BEGIN STRATEGY DECISION

//CHECK FOR GREEN REGIONS
	green_regions = regions.size();
	if (green_pixels.size() > 50)
	{
		instr[H*W] = GREEN_R;
		for (int i = 0; i < green_pixels.size(); ++i)
		{
			if (visited[green_pixels[i].first][green_pixels[i].second] == 0)
				dfs(green_pixels[i].first, green_pixels[i].second, ++green_regions, GREEN);
		}
	}

	if (green_regions - regions.size() > 0)
	{
		if (green_regions - regions.size() == 2)
			instr[H*W+3] = G_BOTH;
		else
		{
			g_barycentre.first = int(g_barycentre.first / g_nodes);
			g_barycentre.second = int(g_barycentre.second / g_nodes);

			int i = 0;
			while (pixel::color(i, g_barycentre.second) != BLACK)
				++i;
			if (!(g_barycentre.first < i))
			{
				i = 0;
				while (pixel::color(g_barycentre.first, i) != BLACK)
					++i;
				if (g_barycentre.second < i)
					instr[H*W+3] = G_LEFT;
				else
					instr[H*W+3] = G_RIGHT;
			}
		}
	}

	int black_regions = count_regions('B');
	int white_regions = count_regions('W');

	instr[H*W+4] = white_regions;
	instr[H*W+5] = black_regions;


//NO GREEN REGIONS FOUND, INTERSECTIONS AND STANDARD LINE
	if (green_regions - regions.size() == 0)
	{
		if (white_regions == 2 && black_regions == 1)
				instr[H*W] = STD_LINE;
	/*	else if (white_regions == 1 && black_regions == 2)
			instr[H*W] = INTERRUPT;*/
		else if (regions.size() > 3)
		{
			if (white_regions == 3)
				instr[H*W] = T_INTERSECTION;
			else if (white_regions == 4)
				instr[H*W] = C_INTERSECTION;
		}
		else if (regions.size() < 3)
		{
			if (find_region('B'))
				instr[H*W] = INTERRUPT;
			//else
				//lost line or gap
		}
	}

	barycentre.first = int(barycentre.first / nodes);
	barycentre.second = int(barycentre.second / nodes);
	instr[H*W+1] = barycentre.first;
	instr[H*W+2] = barycentre.second;

	for (int i = 0; i < 160000; ++i)
		instr[i] = visited[int(i/W)][(i%W)];

	return instr;
}
