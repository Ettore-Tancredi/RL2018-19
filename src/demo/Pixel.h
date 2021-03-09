#ifndef PIXEL_H
#define PIXEL_H

#include "parametri.h"

enum Colors
{
    WHITE = 0,
    BLACK,
    GREEN,
    SILVER,
    UNKNOWN
};
int dataset[256][256][256];

class Pixel
{
private:
    int R,G,B;

public:
    Colors color();
    void fill(int, int, int);
    void get_color(int &, int &, int &);
};


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

Colors Pixel::color()
{
  /*if ((R + G + B)/3 > 75)
		return WHITE;
	else if ((R + G + B)/3 <= 75)
		return BLACK;*/
  if (dataset[R][G][B] == BLACK)
    return BLACK;
  else if (dataset[R][G][B] == WHITE)
    return WHITE;
}

void Pixel::get_color(int &r, int &g, int &b)
{
  r = R;
  g = G;
  b = B;
}

void Pixel::fill(int r, int g, int b)
{
  R = r;
  G = g;
  B = b;
}



#endif
