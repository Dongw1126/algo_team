#include "robot.h"
#include "blueprint.h"
#include <vector>
using namespace std;

int main()
{
	int mapc;
	cout << "���� ���� : ";
	cin >> mapc;
	Map m(blueprints[mapc]);
	robot a;
	int move, type, battery;
	cout << "�̵� ����� �����ϼ���\n1: random move \n2: spin move\n3: zigzag move\n";
	cin >> move;
	cout << "���͸� Ÿ���� �����ϼ���\n1: battery limited type \n2: battery free type\n";
	cin >> type;

	switch (move)
	{
	case 1:
	{
		if (type == 1 || type == 2)
			a.randomMove(m, type);
		else
		{
			cout << "��Ȯ�� Ÿ���� �Է��ϼ���\n";
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
			cout << "��Ȯ�� Ÿ���� �Է��ϼ���\n";
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
			cout << "��Ȯ�� Ÿ���� �Է��ϼ���\n";
			return 0;
		}
		break;
	}
	default:
	{
		cout << "��Ȯ�� �̵������ �Է��ϼ���\n";
		return 0;
	}	
	}
}