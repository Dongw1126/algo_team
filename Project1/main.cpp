#include "robot.h"
#include <vector>
using namespace std;

int main()
{
	vector<vector<int>> my_map1 = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,2,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

	Map m(my_map1);
	robot a;
	a.zigzagMove(m, 1);
}