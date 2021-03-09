#ifndef PIXEL_H
#define PIXEL_H

#include "data_types.h"


namespace pixel
{

	struct Pixel
	{
		uint8_t R;
		uint8_t G;
		uint8_t B;
	};

	Colors color(int i, int j)
	{
		if (img[i][j].R > 200 && img[i][j].G > 200 && img[i][j].B > 200)
			return WHITE;
		else if (img[i][j].R < 50 && img[i][j].G < 50 && img[i][j].B < 50)
			return BLACK;
		else if (img[i][j].R > 150 && img[i][j].G > 150 && img[i][j].B > 150)
			return SILVER;
		else if (img[i][j].R < 50 && img[i][j].G > 100 && img[i][j].B < 50)
			return GREEN;
		else
			return WHITE;
	}

	//Colors color(int i, int j)
	//{
	//	if (img[i][j] == '.')
	//		return WHITE;
	//	else if (img[i][j] == '*')
	//		return BLACK;
	//	else if (img[i][j] == 'V')
	//		return GREEN;
	//}

	bool isInside(int i, int j)
	{
		return i >= 0 && i < H && j >= 0 && j < W;
	}

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

