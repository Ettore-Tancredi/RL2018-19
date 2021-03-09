#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <limits>


#include "cartesian_math.h"
#include "victim_data_structures.h"


/*******************************************************
void tour(number of points)
	Calculates the exact shortest path between all points
******************************************************/
void tour(int S)
{

	double least_dist = std::numeric_limits<double>::max();
	double tot_dist;

	do {
		tot_dist = 0;
		for (int i = 0; i < S; ++i)
		{
			tot_dist += mat[path[i]][path[i+1]];
		}
		tot_dist += mat[0][path[0]];
		tot_dist += mat[S+1][path[S-1]];

		if (tot_dist < least_dist)
		{
			least_dist = tot_dist;
			for (int i = 0; i < S; ++i)
			{
				shortest_path[i] = path[i];
				// std::cout << shortest_path[i] << " ";
			}
				
		}
		// std::cout << "\n";

	} while (std::next_permutation(path.begin(), path.end()));


}


//PYTHON INTERFACE
/*********************************************************
int* load_points(points)
	- Resizes all the path vectors
	- copies the input points into the matrix
	- calculates all the unique distances beetwen
		two points and stores them

	returns the shortest path as list of numbered points
********************************************************/
extern "C" int* load_points(int *array, int N)
{
	int L = N/2;

	for (int i = 0; i < MAX_LOC; ++i)
		res[i] = -1;

	path.resize(L-2);
	points.resize(L);
	shortest_path.resize(L-2);

	for (int i = 0; i < N; i+=2)
	{
		points[i/2].x = array[i];
		points[i/2].y = array[i+1];
	}
	
	// std::cout << std::endl;
	// for (int i = 0; i < L; ++i)
	// {
	// 	std::cout << " (" << points[i].x << ", " << points[i].y << ")" << std::endl;
	// }
	// std::cout << std::endl;


	double dist;
	for (int i = 0; i < L-1; ++i)
	{

		for (int j = i+1; j < L; ++j)
		{
			dist = pitas(points[i].x - points[j].x, points[i].y - points[j].y);
			mat[i][j] = dist;
			mat[j][i] = dist;

			// std::cout << i << " (" << points[i].x << ", " << points[i].y << ")" << "-> " << j << " (" << points[j].x << ", " << points[j].y << ")  :" << mat[i][j] << std::endl; 
		}

	}

	for (int i = 0; i < L-2; ++i)
	{
		path[i] = i+1;
	}
	

	tour(L-2);

	res[0] = 0;
	res[L-1] = L-1;
	for (int i = 0; i < L-2; ++i)
		res[i+1] = shortest_path[i];

	return res;
}
