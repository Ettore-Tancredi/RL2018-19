#include <bits/stdc++.h>

const int MAX_DIM = 1000;

using namespace std;

using pii = pair<int, int>;

enum
{
  WHITE = 0,
  BLACK = 1,
  GREEN = 2,
  SILVER = 3
};

struct Pixel
{
  int r, g, b, C;
};

pii kNN[MAX_DIM];
Pixel trainingSet[MAX_DIM];
int bestColor[4];

int colors[256][256][256];

inline int sqr(int n)
{
  return n*n;
}

void initialize(pii vet[], int k)
{
  for(int i = 0; i < k; i++)
    vet[i] = pii(INT_MAX, WHITE);
}

void Swap(pii &n1, pii &n2)
{
  pii temp = n1;
  n1 = n2;
  n2 = temp;
}

void update(pii vet[], int k, pii dist)
{
  if(dist.first > vet[0].first)
    return;

  vet[0] = dist;

  int i = 1;

  while(i < k && vet[i].first >= vet[i - 1].first)
  {
    Swap(vet[i], vet[i - 1]);
    ++i;
  }


  //for(int i = 1; i < k && vet[i].first >= vet[i - 1].first; i++)
    //Swap(vet[i], vet[i - 1]);
}

void training(string inFileName, string outFileName, const int K)
{
  ifstream in(inFileName);
  ofstream out(outFileName);

  pii tempDist;
  Pixel tempPx;

  int Dim = 0;
  char color;
  while(!in.eof())
  {
    in >> tempPx.r >> tempPx.g >> tempPx.b >> color;

    switch(color)
    {
      case 'w':
        tempPx.C = WHITE;
        break;
      case 'b':
        tempPx.C = BLACK;
        break;
      case 'g':
        tempPx.C = GREEN;
        break;
      case 's':
        tempPx.C = SILVER;
        break;
      default:
        break;
    }

    trainingSet[Dim] = tempPx;
    ++Dim;
  }

  --Dim;

  //for(int i = 0; i < Dim; i++)
    //cout << trainingSet[i].r << " " << trainingSet[i].g << " " << trainingSet[i].b << " " << trainingSet[i].C << endl;

  for(int i = 0; i < 256; i++)
  {
    //cout << i << "esimo ciclo principale\n";
    for(int j = 0; j < 256; j++)
    {
      for(int k = 0; k < 256; k++)
      {
        initialize(kNN, K);
        for(int c = 0; c < Dim; c++)
        {
          tempDist = pii(sqr(i - trainingSet[c].r) + sqr(j - trainingSet[c].g) + sqr(k - trainingSet[c].b), trainingSet[c].C);
          update(kNN, K, tempDist);
        }
        bestColor[WHITE] = 0, bestColor[BLACK] = 0, bestColor[GREEN] = 0, bestColor[SILVER] = 0;

        for(int c = 0; c < K; c++)
          ++bestColor[kNN[c].second];

        int bc = WHITE;
        for(int c = 0; c < 4; c++)
          if(bestColor[c] >= bestColor[bc])
            bc = c;

        colors[i][j][k] = bc;
      }
    }
  }

  for(int i = 0; i < 256; i++)
  {
    for(int j = 0; j < 256; j++)
      for(int k = 0; k < 256; k++)
      {
        out << colors[i][j][k] << " ";
       // cout << i << " " << j << " " << k << " " << colors[i][j][k] << endl;
     //   this_thread::sleep_for(chrono::milliseconds(120));   
      }
  }


}

int main()
{
  string input_file_name = "allenamento.txt";
  string output_file_name = "color_data.txt";

  training(input_file_name, output_file_name, 6);

  return 0;
}

