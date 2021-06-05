#include "map.h"

Map::Map(vector<vector<int> >& _map) {
	width = _map.size();
	height = _map[0].size();

	map = new int* [width];
	for (int i = 0; i < width; i++)
		map[i] = new int[height];

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			map[i][j] = _map[i][j];
		}
	}
}