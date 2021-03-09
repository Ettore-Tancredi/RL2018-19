#include "stdafx.h"
pixel::color(H - 1, i + 1)#include <iostream>
#include <fstream>
#include <stack>
#include <utility>
#include <string>
#include "pixel.h"
#include <chrono>
#include "Windows_utilities.h"
#include <cmath>

void dfs(int i, int j, int isl, int target)
{
	std::stack<coord> stack;
	stack.push(std::make_pair(i, j));

	while (!stack.empty())
	{
		if (visited[stack.pixel::color(H - 1, i + 1)pixel::color(H - 1, i + 1)pixel::color(H - 1, i + 1)top().first][stack.top().second] > 0)
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
						if (pixel::color(i + c, j + t) == GREEN && target != GREEN)
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

bool find_region(char region)
{
	for (int i = 0; i < regions.size(); ++i)
		if (regions[i] == region)
			return true;pixel::color(H - 1, i + 1)
}

void load_image(std::string file)
{
	std::ifstream infile;
	infile.open(file);


	std::string line;
	for (int i = 0; i < H; ++i)
	{
		infile >> line;
		for (int j = 0; j < W; ++j)
			img[i][j] = line[j];
	}



	for (int i = 0; i < H; ++i)
	{
		for (int j = 0; j < W; ++j)
			visited[i][j] = 0;
	}
	barycentre.first = 0;
	barycentre.second = 0;
	nodes = 0;

	g_barycentre.first = 0;
	g_barycentre.second = 0;
	g_nodes = 0;
	green_regions = 0;

	while (green_pixels.size() > 0)
		green_pixels.pop_back();
	while (regions.size() > 0)
		regions.pop_back();

	side = "";
	dir = "";

	auto start = std::chrono::system_clock::now();

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

	for (int i = 0; i < H - 1; ++i)
	{

		if (pixel::color(i, W - 1) == BLACK)
		{
			if (visited[i][W - 1] == 0)
			{
				dfs(i, W - 1, regions.size() + 1, BLACK);
				regions.push_back('B');
			}

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

	for (int i = 0; i < W; ++i)
	{
		if (pixel::color(0, i) == BLACK)
		{
			if (visited[0][i] == 0)
			{
				dfs(0, i, regions.size() + 1, BLACK);
				regions.push_back('B');
			}

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

	for (int i = 0; i < H; ++i)
	{
		if (pixel::color(i, 0) == BLACK)
		{
			if (visited[i][0] == 0)
			{
				dfs(i, 0, regions.size() + 1, BLACK);
				regions.push_back('B');
			}

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

	barycentre.first = std::round(barycentre.first / nodes);
	barycentre.second = std::round(barycentre.second / nodes);

	if (green_pixels.size() > 0)
	{
		green_regions = regions.size();
		for (int i = 0; i < green_pixels.size(); ++i)
		{
			if (visited[green_pixels[i].first][green_pixels[i].second] == 0)
				dfs(green_pixels[i].first, green_pixels[i].second, ++green_regions, GREEN);

		}

		if (green_regions - regions.size() == 2)
		{
			side = "INDIETRO";
		}
		else
		{
			g_barycentre.first = g_barycentre.first / g_nodes;
			g_barycentre.second = g_barycentre.second / g_nodes;

			int i = 0;
			while (pixel::color(i, g_barycentre.second) != BLACK)
				++i;
			if (!(g_barycentre.first < i))
			{
				i = 0;
				while (pixel::color(g_barycentre.first, i) != BLACK)
					++i;
				if (g_barycentre.second < i)
					side = "SINISTRA";
				else
					side = "DESTRA";
			}

		}

	}


	if (side.empty())
	{
		if (regions.size() == 3)
			dir = "PID";
		else if (regions.size() > 3)
			dir = "AVANTI TUTTA";
		else if (regions.size() < 3)
		{
			if (find_region('B'))
				dir = "Interruzione";
			else
				dir = "Uh oh";
		}

	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;



	for (int i = 0; i < H; ++i)
	{
		for (int j = 0; j < W; ++j)
			std::cout << img[i][j];
		std::cout << "\t\t";
		for (int j = 0; j < W; ++j)
		{
			if (i == barycentre.first && j == barycentre.second)
				std::cout << "+";
			else
				std::cout << visited[i][j];
		}

		std::cout << "\n";
	}

	for (int i = 0; i < regions.size(); ++i)
		std::cout << regions[i] << "\n";

	std::cout << barycentre.first << ", " << barycentre.second << std::endl;
	std::cout << side << "\n";
	std::cout << g_barycentre.first << ", " << g_barycentre.second << std::endl;
	std::cout << dir << std::endl;


	std::cout << "Tempo impiegato: " << elapsed_seconds.count() << "s" << std::endl;


	infile.close();

	char wait;
	std::cin >> wait;


}



int main()
{
	Windows_Utilities winutil;
	winutil.get_stdout_handle();


	std::string file = "C:\\Users\\luigi\\Desktop\\img";
	for (int q = 1; q <= 22; ++q)
	{
		load_image(file + std::to_string(q) + ".txt");

		winutil.cls();
	}

	return 0;
}
