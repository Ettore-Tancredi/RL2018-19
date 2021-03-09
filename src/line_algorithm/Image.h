#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <iostream> //debug purposes
#include <string>
#include <fstream>

#include "Pixel.h"
#include "Line.h"


class Image
{
private:
    static const int H = 200;
    static const int W = 200;

    Pixel val[H][W];
    void filter(int, int);
    Colors mostFrequentNeightbour(int, int );
    std::vector<char>regions;

    std::vector<coord> green_pixels;

public:
    void copy(int mat[H][W][4]);
   // void load_training_data(std::string);
    int visited[H][W];
    int height();
    int width();
    bool is_inside(int, int);

    Colors px_color(int, int);
    bool isValid(int, int, int);

    int num_regions();
    bool find_region(char);
    int count_regions(char);
    void add_region(char);

    int num_G_pixels();
    void add_px(int, int);
    int green_regions;

    coord Gpx_coord(int);

    void get_debug_color(int, int, int &, int &, int &);
};


coord Image::Gpx_coord(int i)
{
  return green_pixels[i];
}


void Image::get_debug_color(int i, int j, int &t1, int &t2, int &t3)
{
  val[i][j].get_color(t1, t2, t3);
}

void Image::copy(int mat[H][W][4])
{
  int t1, t2, t3;
  for (int i = 0; i < H; ++i)
  {
    for (int j = 0; j < W; ++j)
    {
      t1 = mat[i][j][0];
      t2 = mat[i][j][1];
      t3 = mat[i][j][2];

      val[i][j].fill(t1, t2, t3);
      visited[i][j] = 0;
    }
  }

  regions.clear();
  green_pixels.clear();
  green_regions = 0;

}

bool Image::find_region(char region_type)
{
    for (auto &i: regions)
    {
        if (i == region_type)
            return true;
    }
    return false;
}

int Image::count_regions(char region_type)
{
    int count = 0;
    for (auto &i: regions)
    {
        if (i == region_type)
            ++count;
    }
    return count;
}


int Image::num_regions()
{
    return regions.size();
}

Colors Image::mostFrequentNeightbour(int i, int j)
{
  int i_adj[] = {0, 1, 1, 1, 0, -1, -1, -1};
  int j_adj[] = {1, 1, 0, -1, -1, -1, 0, 1};

  Colors temp;
  int new_i, new_j;
  int whites = 0, blacks = 0, greens = 0, silvers = 0;

  for(int c = 0; c < 8; c++)
  {
    new_i = i + i_adj[c];
    new_j = j + j_adj[c];
    if(0 <= new_i && new_i < H && 0 <= new_j && new_j < W)
    {
      temp = val[new_i][new_j].color();
      switch(temp)
      {
        case WHITE:
          ++whites;
        case BLACK:
          ++blacks;
        case GREEN:
          ++greens;
        case SILVER:
          ++silvers;
        default:
          ++whites;     // onde evitare casini inimmaginabili nel caso di 2 UNKNOWN vicini, ci limitiamo a restituire il valore più probabile
      }
    }
  }

  int massValue = 0;
  temp = WHITE;

  if(whites >= massValue)
  {
    massValue = whites;
    temp = WHITE;
  }
  if(blacks >= massValue)
  {
    massValue = blacks;
    temp = BLACK;
  }
  if(greens >= massValue)
  {
    massValue = greens;
    temp = GREEN;
  }
  if(silvers >= massValue)
  {
    massValue = silvers;
    temp = SILVER;
  }

  return temp;
}

Colors Image::px_color(int i, int j)
{
    Colors col = val[i][j].color();
    /*if (col == UNKNOWN)
    {
        filter(i, j);
        col = val[i][j].color();
        if (col == UNKNOWN)
          col = mostFrequentNeightbour(i, j);
    }*/

    return col;
}

int Image::width()
{
    return W;
}
int Image::height()
{
    return H;
}

void Image::filter(int i, int j)
{
  int i_adj[] = {0, 1, 1, 1, 0, -1, -1, -1};
  int j_adj[] = {1, 1, 0, -1, -1, -1, 0, 1};
  int R_temp, G_temp, B_temp;

  val[i][j].get_color(R_temp, G_temp, B_temp);
  int num = 1;
  int R_media = R_temp;
  int G_media = G_temp;
  int B_media = B_temp;

  int new_i, new_j;

  for(int c = 0; c < 8; c++)
  {
    new_i = i + i_adj[c];
    new_j = j + j_adj[c];
    if(0 <= new_i && new_i < H && 0 <= new_j && new_j < W)
    {
      val[new_i][new_j].get_color(R_temp, G_temp, B_temp);
      R_media += R_temp;
      G_media += G_temp;
      B_media += B_temp;
      ++num;
    }
  }

  val[i][j].fill(int(R_media / num), int(G_media / num), int(B_media / num));
}


int Image::num_G_pixels()
{
  return green_pixels.size();
}

void Image::add_px(int i, int j)
{
  green_pixels.push_back(std::pair<int, int>(i, j));
}

void Image::add_region(char region)
{
  regions.push_back(region);
}

bool Image::is_inside(int i, int j)
{
  return (i >= 0 && i < H && j >= 0 && j < W);
}

bool Image::isValid(int i, int j, int target)
{
    bool val = false;

		for (int c = -1; c < 2; ++c)
			for (int t = -1; t < 2; ++t)
				if (is_inside(i + c, j + t) && !(c == 0 && t == 0))
        {
          if (target == BLACK && (px_color(i+c, j+t) == GREEN || px_color(i+c, j+t) == WHITE || (i == 0 || i == H - 1 || j == 0 || j == W - 1)))
            val |= true;
          else if (target == WHITE && (px_color(i+c, j+t) == BLACK || px_color(i+c, j+t) == GREEN|| (i == 0 || i == H - 1 || j == 0 || j == W - 1)))
            val|= true;
          else if (target == GREEN && (px_color(i+c, j+t) == BLACK || px_color(i+c, j+t) == WHITE || (i == 0 || i == H - 1 || j == 0 || j == W - 1)))
            val|= true;  
        }

		return val;
}


#endif
