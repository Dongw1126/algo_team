#pragma once
#include <vector>
using namespace std;

class Map
{
public:
	int width;
	int height;
	int** map;

	Map(vector<vector<int>>& _map);
};