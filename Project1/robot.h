#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "map.h"

using namespace std;

// �Ʒ�, ��, ������, ����
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

class robot
{
private:
    int x, y;
public:
    robot();

    // type 1 : �ð� ������ �ΰ� �˰��� ����
    // type 2 : �ð������� �����ʰ� coverage 100%�� �޼��� ������ ����
	void randomMove(Map map, int type);
	void spinMove(Map map, int type);
	void zigzagMove(Map map, int type);
	void printMap(Map& map);
};

robot::robot() {
    x = 0; y = 0;
}

void robot::printMap(Map& map)
{
    const string a = "��";  //��
    const string b = "��";  //û������ ��������
    const string c = "��"; //�κ�û�ұ�
    const string d = "��"; // û�� �Ϸ�

    for (int i = 0; i < map.width; i++)
    {
        for (int j = 0; j < map.height; j++)
        {
            switch (map.map[i][j])
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
            case 3:
                cout << d;
                break;
            }
        }
        cout << endl;
    }
}

void robot::randomMove(Map map, int type)
{
    for (int i = 0; i < map.width; i++) {
        for (int j = 0; j < map.height; j++) {
            if (map.map[i][j] == 2) {
                this->x = i;
                this->y = j;
            }
        }
    }
    srand((unsigned)time(NULL));

    int calc_cost = 0; // ���� Ƚ��
    int time_cost = 0; // �ҿ� �ð�
    int time_limit = 100; // �ð� ����
    int coverage = 0; // û�� ����

    int map_size = map.width * map.height;

    while (true) {
        int dir = rand() % 4;
        int distance = (rand() % max(map.height, map.width)) + 1;
        calc_cost += 2;

        while ((distance > 0) && (map.map[this->x + dx[dir]][this->y + dy[dir]] != 1)) {
            distance--;
            map.map[x][y] = 3; // û�� �Ϸ� ǥ��

            this->x += dx[dir];
            this->y += dy[dir];
            map.map[x][y] = 2;

            calc_cost += 3;
            time_cost++;
            if (type == 1) {
                if (time_limit <= time_cost) {
                    break;
                }
            }

            // û�� ���� ��� (���� ������ ��)
            system("cls");
            this->printMap(map);
            Sleep(10);
        }

        coverage = 0;
        for (int i = 0; i < map.width; i++)
            for (int j = 0; j < map.height; j++)
                if (map.map[i][j] != 0)
                    coverage++;

        // 1�� : �ð������� �ΰ� �˰����� ����
        if (type == 1) {
            if (time_limit <= time_cost) {
                break;
            }
        }

        // 2�� : �ð������� �����ʰ� coverage 100%�� �޼��� ������ ����
        if (type == 2) {
            // cout << coverage << endl;
            if (coverage == map_size) {
                break;
            }
        }
    }

    cout << "��ũ�� Ŀ������ ����Ƚ�� �ҿ�ð�" << endl;

    // �� ũ�� ���
    cout << map_size << " ";

    // û�� ���� ���
    float coverage_rate = ((float)coverage / (map.width * map.height)) * 100;
    cout << coverage << " ";

    // ���� Ƚ�� ���
    cout << calc_cost << " ";

    // �ҿ� �ð� ���
    cout << time_cost << " ";
}

void robot::spinMove(Map map, int type)
{

}

void robot::zigzagMove(Map map, int type)
{

}

