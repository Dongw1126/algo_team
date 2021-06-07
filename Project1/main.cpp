#include "robot.h"
#include "blueprint.h"
#include <vector>
using namespace std;

int main()
{
	int mapc;
	cout << "지도 선택 : ";
	cin >> mapc;
	Map m(blueprints[mapc]);
	robot a;
	int move, type, battery;
	cout << "이동 방식을 선택하세요\n1: random move \n2: spin move\n3: zigzag move\n";
	cin >> move;
	cout << "배터리 타입을 선택하세요\n1: battery limited type \n2: battery free type\n";
	cin >> type;

	switch (move)
	{
	case 1:
	{
		if (type == 1 || type == 2)
			a.randomMove(m, type);
		else
		{
			cout << "정확한 타입을 입력하세요\n";
			return 0;
		}
		break;
	}

	case 2:
	{
		if (type == 1 || type == 2)
			a.spinMove(m, type);
		else
		{
			cout << "정확한 타입을 입력하세요\n";
			return 0;
		}
		break;
	}

	case 3:
	{
		if (type == 1 || type == 2)
			a.zigzagMove(m, type);
		else
		{
			cout << "정확한 타입을 입력하세요\n";
			return 0;
		}
		break;
	}
	default:
	{
		cout << "정확한 이동방식을 입력하세요\n";
		return 0;
	}	
	}
}