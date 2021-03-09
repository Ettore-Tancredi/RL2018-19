#include <bits/stdc++.h>

using namespace std;

map<int, int> points;


int main()
{

    points.insert({5, 0});
    points.insert({5, 32});


    for (auto i : points)
        cout << i.first <<  " " << i.second; 

}