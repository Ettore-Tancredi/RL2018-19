#include <iostream>
#include <fstream>
#include <stack>
#include <utility>
#include <string>
#include <chrono>
#include <cmath>
#include <map>

#include "Image.h"
#include "Pixel.h"
#include "Line.h"

Image img;
Line line;
const int H = 200;
const int W = 200;
int instr[H*W+400];
const int MIN_NODES = 20;


std::map<int, int> points;
int sides[4];
//int map[160005];

/****************************************************************************************
void dfs(start i_coordinate, start j_coordinate, region number, validation criteria)
	- Beginning from the start pixel, it explores all adjacent pixels that satisfy the
		input criteria (i.e. the desired color) and that haven't been visited yet.
	- While exploring, it marks all the pixels it finds with the region number at the
		corrisponding indexes	in the "visited" matrix.
	- It ends once it can no longer find acceptable pixels.
***********************************************************************************/
int dfs(int i, int j, int isl, int target)
{
	std::stack<coord> stack;
	stack.push(std::make_pair(i, j));
	int reg_nodes = 0;
	coord green_bg;
	int num_g_nodes = 1;
	while (!stack.empty())
	{
		if (img.visited[stack.top().first][stack.top().second] > 0)
		{
			stack.pop();
		}
		else
		{
			int i = stack.top().first;
			int j = stack.top().second;
			for (int c = -1; c < 2; ++c)
				for (int t = -1; t < 2; ++t)
					if (img.is_inside(i + c, j + t) && !(c == 0 && t == 0))
					{
						if (img.isValid(i + c, j + t, target) && (img.visited[i + c][j + t] == 0) && img.px_color(i+c, j+t) == target)
						{
							stack.push(std::make_pair(i + c, j + t));
							
						}
							

						//look for green pixels adjacent to the borders of the black line
					if (img.px_color(i + c, j + t) == GREEN && target == BLACK)
							img.add_px(i + c, j + t);
					}

			if (target == BLACK)
			{
				line.barycentre.first += i;
				line.barycentre.second += j;
				points.insert({img.height()-i, j-img.width()/2});
				++line.num_nodes;
			}
			else if (target == GREEN)
			{
				green_bg.first += i;
				green_bg.second += j;
				++num_g_nodes;
			}
			img.visited[i][j] = isl;
			++reg_nodes;
		}
	}
	if(target == GREEN)
	{
		coord temp;
		temp = coord(int(green_bg.first / num_g_nodes), int(green_bg.second / num_g_nodes));
		line.green_regions.push_back(temp);
	}

	return reg_nodes;
}


extern "C" void load_training_data()
{
  std::ifstream in("color_data.txt");

  for (int i = 0; i < 256; ++i)
  {
    for (int j = 0; j < 256; ++j)
    {
      for (int k = 0; k < 256; ++k)
        in >> dataset[i][j][k];
    }
  }

  in.close();
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

extern "C" int* load_image(int arr[H][W][4])
{
	img.copy(arr);
//	img.load_training_data("data.txt");
	line.barycentre.first = 0;
	line.barycentre.second = 0;
	line.num_nodes = 1;
	instr[img.height()*img.width()+6] = 0;
	bool skippa = false;
	
	int reg_nodes;
//BOTTOM
	for (int i = 0; i < img.width(); ++i)
	{
		if (img.px_color(img.height() - 1, i) == BLACK)
		{
			if (img.visited[img.height()- 1][i] == 0)
			{
				reg_nodes = dfs(img.height()- 1, i, img.num_regions() + 1, BLACK);
				if (reg_nodes > MIN_NODES)
					img.add_region('B');
			}

			if (img.px_color(img.height()- 1, i - 1) == WHITE && img.visited[img.height()- 1][i - 1] == 0)
			{
				reg_nodes = dfs(img.height()- 1, i - 1, img.num_regions() + 1, WHITE);
				if (reg_nodes > MIN_NODES)
					img.add_region('W');
			}

			while (img.px_color(img.height()- 1, i) == BLACK)
			{
				++i;
				if (i >= img.width()-1)
				{
					++instr[img.height()*img.width()+6];
					skippa = true;
					break;
				}				
			}
			if (!skippa)
			{
				if (img.px_color(img.height()- 1, i + 1) == WHITE && img.visited[img.height()- 1][i + 1] == 0)
				{
					reg_nodes = dfs(img.height() - 1, i + 1, img.num_regions() + 1, WHITE);
					if (reg_nodes > MIN_NODES)
						img.add_region('W');
				}
			}

		}

	}

	skippa = false;

//LEFT
	for (int i = 0; i < img.height()- 1; ++i)
	{

		if (img.px_color(i, img.width() - 1) == BLACK)
		{
			if (img.px_color(i - 1, img.width() - 1) == WHITE && img.visited[i - 1][img.width() - 1] == 0)
			{
				reg_nodes = dfs(i - 1, img.width() - 1, img.num_regions() + 1, WHITE);
				if (reg_nodes > MIN_NODES)
					img.add_region('W');
			}

			while (img.px_color(i, img.width() - 1) == BLACK)
			{
				++i;
				if (i >= img.height()-1)
				{
					++instr[img.height()*img.width()+6];
					skippa = true;
					break;
				}				
			}
			if (!skippa)
			{
				if (img.px_color(i + 1, img.width() - 1) == WHITE && img.visited[i + 1][img.width() - 1] == 0)
				{
					reg_nodes = dfs(i + 1, img.width() - 1, img.num_regions() + 1, WHITE);
					if (reg_nodes > MIN_NODES)
						img.add_region('W');
				}
			}
			
		}
	}

	skippa = false;
//UP
	for (int i = 0; i < img.width(); ++i)
	{
		if (img.px_color(0, i) == BLACK)
		{
			if (img.px_color(0, i - 1) == WHITE && img.visited[0][i - 1] == 0)
			{
				reg_nodes = dfs(0, i - 1, img.num_regions() + 1, WHITE);
				if (reg_nodes > MIN_NODES)
					img.add_region('W');
			}

			while (img.px_color(0, i) == BLACK)
			{
				++i;
				if (i >= img.width()-1)
				{
					++instr[img.height()*img.width()+6];
					skippa = true;
					break;
				}				
			}
			if (!skippa)
			{
				if (img.px_color(0, i + 1) == WHITE && img.visited[0][i + 1] == 0)
				{
					reg_nodes = dfs(0, i + 1, img.num_regions() + 1, WHITE);
					if (reg_nodes > MIN_NODES)
						img.add_region('W');
				}
			}


		}
	}

	skippa = false;

//RIGHT
	for (int i = 0; i < img.height(); ++i)
	{
		if (img.px_color(i, 0) == BLACK)
		{
			if (img.px_color(i - 1, 0) == WHITE && img.visited[i - 1][0] == 0)
			{
				reg_nodes = dfs(i - 1, 0, img.num_regions() + 1, WHITE);
				if (reg_nodes > MIN_NODES)
					img.add_region('W');
			}

			while (img.px_color(i, 0) == BLACK)
			{
				++i;
				if (i >= img.height()-1)
				{
					++instr[img.height()*img.width()+6];
					skippa = true;
					break;
				}				
			}
			if (!skippa)
			{
				if (img.px_color(i + 1, 0) == WHITE && img.visited[i + 1][0] == 0)
				{
					reg_nodes = dfs(i + 1, 0, img.num_regions() + 1, WHITE);
					if (reg_nodes > MIN_NODES)
						img.add_region('W');
				}
			}

		}
	}

	bool green_found = false;
	int j, k;
	if (img.num_G_pixels() > MIN_NODES)
	{
		for (int i = 0; i < img.num_G_pixels(); ++i)
		{
			j = img.Gpx_coord(i).first;
			k = img.Gpx_coord(i).second;
			if (img.visited[j][k] == 0)
			{
				reg_nodes = dfs(j, k, img.num_regions()+line.green_regions.size()+1, GREEN);
				if (reg_nodes > MIN_NODES)
				{
					//++img.green_regions;   abbiamo già incrementato la dimensione di line.green_regions
					green_found = true;
				}
				else
				{
					line.green_regions.pop_back();
				}
				
			}
		}
	}
	int black_regions = img.count_regions('B');
	int white_regions = img.count_regions('W');
	bool green_positions[2][2];

	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			green_positions[i][j] = false;

	if (green_found)
	{

		int i, j;
		for(int k = 0; k < line.green_regions.size(); ++k)
		{
			i = 0, j = 0;
			while(img.px_color(i, line.green_regions[k].second) != BLACK && i < img.height())
				++i;

			while(img.px_color(line.green_regions[k].first, j) != BLACK && j < img.width())
				++j;

			if(i > line.green_regions[k].first)
			{
				if(j > line.green_regions[k].second)
					green_positions[0][0] = true;
				else
					green_positions[0][1] = true;
			}
			else
			{
				if(j > line.green_regions[k].second)
					green_positions[1][0] = true;
				else
					green_positions[1][1] = true;
			}
				
		}

		if(green_positions[1][0] && green_positions[1][1])
			instr[img.height() * img.width()] = GREEN_BOTH;

		else if(green_positions[1][0] && !green_positions[1][1])
			instr[img.height() * img.width()] = GREEN_LEFT;

		else if(!green_positions[1][0] && green_positions[1][1])
			instr[img.height() * img.width()] = GREEN_RIGHT;
		
	}
	if (!(green_positions[1][1] || green_positions[1][0]))
	{
		//NO GREEN REGIONS FOUND, INTERSECTIONS AND STANDARD LINE
		if (white_regions == 2 && black_regions == 1)
				instr[img.height()*img.width()+0] = STD_LINE;
		else if (img.num_regions() > 3)
		{
			if (white_regions == 3)
				instr[img.height()*img.width()+0] = T_INTERSECTION;
			else if (white_regions == 4)
				instr[img.height()*img.width()+0] = C_INTERSECTION;
		}
		else if (img.num_regions() < 3)
		{
			if (img.find_region('B'))
				instr[img.height()*img.width()+0] = INTERRUPT;
			//else
				//lost line or gap
		}
	}
	

	for (int j = 0; j < img.width(); ++j)
	{
		if (img.visited[0][j] == 1)
			sides[0] = true;
		if (img.visited[img.height()-1][j] == 1)
			sides[2] = true;		
	}
	for (int i = 0; i < img.width(); ++i)
	{
		if (img.visited[i][0] == 1)
			sides[1] = true;
		if (img.visited[i][img.width()-1] == 1)
			sides[3] = true;		

	}


	instr[img.height()*img.width()+4] = white_regions;
	instr[img.height()*img.width()+5] = black_regions;
	line.barycentre.first = int(line.barycentre.first / line.num_nodes);
	line.barycentre.second = int(line.barycentre.second / line.num_nodes);
	instr[img.height()*img.width()+1] = line.barycentre.first;
	instr[img.height()*img.width()+2] = line.barycentre.second;
	
	for (int i = 0; i < img.height()*img.width(); ++i)
		instr[i] = img.visited[int(i/img.width())][(i%img.width())];


	points.erase(points.begin());
	std::ofstream out("tan.txt");
	int k = 6;
	for (auto i: points)
	{

		instr[img.height()*img.width()+k] = i.second;
		instr[img.height()*img.width()+k+1] = i.first;
		k +=2;
	}
		
	
	out.close();
		
	return instr;
}
