#pragma once
#include <iostream>
#include <string>
#include "map1.h"

using namespace std;

class robot
{
private:

public:
	void randomMove(int* ary);
	void spinMove(int* ary);
	void zigzagMove(int* ary);
	void printMap();
};

void robot::printMap()
{
    const string a = "��";  //��
    const string b = "��";  //û������ ��������
    const string c = "��"; //�κ�û�ұ�

    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            switch (map[i][j])
            {
            case 0:
                cout << b;
                break;
            case 1:
                cout << a;
                break;
            case 2:
                cout << c;
                break;
            }
        }
        cout << endl;
    }
}

void robot::randomMove(int* ary)
{

}

void robot::spinMove(int* ary)
{

}

void robot::zigzagMove(int* ary)
{

}

