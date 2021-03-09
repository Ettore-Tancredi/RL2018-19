#ifndef PIXEL_DEMO_H
#define PIXEL_DEMO_H

#include "line_data_structures_demo.h"


int max(int a, int b, int c)
{
	if (a > b && a > c)
		return a;
	else if (b > a && b > c)
		return b;
	else
		return c;
}

int min(int a, int b, int c)
{
	if (a < b && a < c)
		return a;
	else if (b < a && b < c)
		return b;
	else
		return c;
}

int diff(int A, int B)
{
	return A-B;
}

bool isGreen(int R, int G, int B)
{
	return (G > R && G > B && (diff(G, B) > 1 || diff(G, R) > 1));
}
	

namespace pixel
{
	Colors color(int i, int j)
	{
	if (((img[i][j].R + img[i][j].G + img[i][j].B)/3 < 110) && (max(img[i][j].R, img[i][j].G, img[i][j].B) - min(img[i][j].R, img[i][j].G, img[i][j].B) >= 25))
 		return GREEN;
	else if ((img[i][j].R + img[i][j].G + img[i][j].B)/3 > 65)
		return WHITE;
	else if (((img[i][j].R + img[i][j].G + img[i][j].B)/3 <= 65))
		return BLACK;
	}

	bool isInside(int i, int j)
	{
		return i >= 0 && i < H && j >= 0 && j < W;
	}


	/******************************************************************
	bool isValid(pixel coord_i, pixel coord_j, target color)
		Based on the target, it decides if a color is acceptable or not.
		A pixel is classified as acceptable if:
	 	 - it's located on the border of the image
		 - it has at least one neighbouring pixel of a different colors
		return TRUE if it's acceptable
	*****************************************/
	bool isValid(int i, int j, int target)
	{
		bool val = false;

		for (int c = -1; c < 2; ++c)
			for (int t = -1; t < 2; ++t)
				if (isInside(i + c, j + t) && !(c == 0 && t == 0))
					val |= (color(i + c, j + t) == (target == BLACK ? WHITE : target == WHITE ? BLACK : color(i + c, j + t) == WHITE ? WHITE : BLACK)) || (color(i + c, j + t) == GREEN && !(target == GREEN)) || (i == 0 || i == H - 1 || j == 0 || j == W - 1);

		return val;
	}

}



#endif // !PIXEL_H
