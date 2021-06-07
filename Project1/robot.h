#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
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
	void renderMap(Map& map);
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

void robot::renderMap(Map& map) {
	system("cls");
	this->printMap(map);
	Sleep(10);
}

void robot::zigzagMove(Map map, int type)
{
	for (int i = 0; i < map.width; i++)
	{
		for (int j = 0; j < map.height; j++)
		{
			if (map.map[i][j] == 2)
			{
				this->x = i;
				this->y = j;
			}
		}
	}

	srand((unsigned)time(NULL));

	int map_calc = 0;
	int memory_calc = 0;
	int move_calc = 0;
	int calc_cost = 0;
	//���� �������� ����� ����

	int time_cost = 0; // �ҿ� �ð�
	int time_limit = 100; // �ð� ����(�ܿ� ���͸�)
	int half_time_limit = time_limit / 2;

	int coverage = 0; // û�� ����
	int room_size = 0; // �� ����
	for (int i = 0; i < map.width; i++)
		for (int j = 0; j < map.height; j++)
			if (map.map[i][j] != 1)
				room_size++;
	int map_size = map.width * map.height; //��ü ����

	int dir;
	enum dirc { DOWN, UP, RIGHT, LEFT }; //���� ������

	vector<pair<int, int> > back_path; //��Ʈ��ŷ�� �߰� �޸�

	dir = LEFT;


	while (true)
	{
		while ((map.map[this->x + dx[DOWN]][this->y + dy[DOWN]] != 1) || (map.map[this->x + dx[UP]][this->y + dy[UP]] != 1) ||
			(map.map[this->x + dx[RIGHT]][this->y + dy[RIGHT]] != 1) || (map.map[this->x + dx[LEFT]][this->y + dy[LEFT]] != 1))
		{

			

			if ((map.map[this->x + dx[dir]][this->y + dy[dir]] != 1) && (map.map[this->x + dx[dir]][this->y + dy[dir]] != 3))	//�κ� ���� ����, ���� ���̳�, û���� ���� �ƴҰ��
			{
				if (dir == LEFT)
				{
					if (map.map[this->x + dx[DOWN]][this->y + dx[DOWN]] == 0)	//��ֹ� ����ġ�� �ʵ��� �� ����
					{
						map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��
						map_calc += 1;

						dir = DOWN;
						this->x += dx[dir];
						this->y += dy[dir];
						map.map[this->x][this->y] = 2;
						move_calc += 1;

						back_path.push_back({ dx[dir] * (-1), dy[dir] * (-1) });
						memory_calc += 1;
					}
					else if ((map.map[this->x + dx[DOWN]][this->y + dx[DOWN]] == 1) || (map.map[this->x + dx[DOWN]][this->y + dx[DOWN]] == 3))	// �Ʒ��� û���Ѱ��̰ų� ���� ���
					{
						map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��
						map_calc += 1;

						dir = LEFT;
						this->x += dx[dir];
						this->y += dy[dir];
						map.map[this->x][this->y] = 2;
						move_calc += 1;

						back_path.push_back({ dx[dir] * (-1), dy[dir] * (-1) });
						memory_calc += 1;
					}
				}
				else if (dir == UP)
				{
					if (map.map[this->x + dx[LEFT]][this->y + dx[LEFT]] == 0)	//��ֹ� ����ġ�� �ʵ��� �� ����
					{
						map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��
						map_calc += 1;

						dir = LEFT;
						this->x += dx[dir];
						this->y += dy[dir];
						map.map[this->x][this->y] = 2;
						move_calc += 1;

						back_path.push_back({ dx[dir] * (-1), dy[dir] * (-1) });
						memory_calc += 1;
					}
					else if ((map.map[this->x + dx[LEFT]][this->y + dx[LEFT]] == 1) || (map.map[this->x + dx[LEFT]][this->y + dx[LEFT]] == 3))	// �Ʒ��� û���Ѱ��̰ų� ���� ���
					{
						map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��
						map_calc += 1;

						dir = UP;
						this->x += dx[dir];
						this->y += dy[dir];
						map.map[this->x][this->y] = 2;
						move_calc += 1;

						back_path.push_back({ dx[dir] * (-1), dy[dir] * (-1) });
						memory_calc += 1;
					}
				}
				else if (dir == RIGHT)
				{
					if (map.map[this->x + dx[UP]][this->y + dx[UP]] == 0)	//��ֹ� ����ġ�� �ʵ��� �� ����
					{
						map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��
						map_calc += 1;

						dir = UP;
						this->x += dx[dir];
						this->y += dy[dir];
						map.map[this->x][this->y] = 2;
						move_calc += 1;

						back_path.push_back({ dx[dir] * (-1), dy[dir] * (-1) });
						memory_calc += 1;
					}
					else if ((map.map[this->x + dx[UP]][this->y + dx[UP]] == 1) || (map.map[this->x + dx[UP]][this->y + dx[UP]] == 3))	// �Ʒ��� û���Ѱ��̰ų� ���� ���
					{
						map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��
						map_calc += 1;

						dir = RIGHT;
						this->x += dx[dir];
						this->y += dy[dir];
						map.map[this->x][this->y] = 2;
						move_calc += 1;

						back_path.push_back({ dx[dir] * (-1), dy[dir] * (-1) });
						memory_calc += 1;
					}
				}
				else if (dir == DOWN)
				{
					if (map.map[this->x + dx[RIGHT]][this->y + dx[RIGHT]] == 0)	//��ֹ� ����ġ�� �ʵ��� �� ����
					{
						map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��
						map_calc += 1;

						dir = RIGHT;
						this->x += dx[dir];
						this->y += dy[dir];
						map.map[this->x][this->y] = 2;
						move_calc += 1;

						back_path.push_back({ dx[dir] * (-1), dy[dir] * (-1) });
						memory_calc += 1;
					}
					else if ((map.map[this->x + dx[RIGHT]][this->y + dx[RIGHT]] == 1) || (map.map[this->x + dx[RIGHT]][this->y + dx[RIGHT]] == 3))	// �Ʒ��� û���Ѱ��̰ų� ���� ���
					{
						map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��
						map_calc += 1;

						dir = DOWN;
						this->x += dx[dir];
						this->y += dy[dir];
						map.map[this->x][this->y] = 2;
						move_calc += 1;

						back_path.push_back({ dx[dir] * (-1), dy[dir] * (-1) });
						memory_calc += 1;
					}
				}
				
			}			
			//����� �� Ȥ�� �̹� û���ߴ� ������ ���, ���� ����� ��������� ��Ʈ��ŷ�Ͽ� �̵�
			else /*if (!((map.map[this->x + dx[DOWN]][this->y + dy[DOWN]] == 0) || (map.map[this->x + dx[UP]][this->y + dy[UP]] == 0) ||
				 (map.map[this->x + dx[RIGHT]][this->y + dy[RIGHT]] == 0) || (map.map[this->x + dx[LEFT]][this->y + dy[LEFT]] == 0)))*/
			{
				int i = back_path.size() - 1;

				this->x += back_path[i].first;
				this->y += back_path[i].second;
				map.map[this->x][this->y] = 2;
				move_calc += 1;

				back_path.pop_back();
				memory_calc += 1;
			}

			calc_cost = map_calc + move_calc + memory_calc;
			time_cost++;

			if (type == 1) {
				if (half_time_limit <= time_cost) {
					break;
				}
			}

			// û�� ���� ��� (���� ������ ��)
			this->renderMap(map);
		}

		coverage = 0;

		for (int i = 0; i < map.width; i++)
			for (int j = 0; j < map.height; j++)
				if (map.map[i][j] == 3)
					coverage++;

		// 1�� : �ð������� �ΰ� �˰����� ����
		if (type == 1) {
			if (coverage / room_size == 1) {
				break;
			}

			if (half_time_limit <= time_cost) {
				break;
			}
		}

		// 2�� : �ð������� �����ʰ� coverage 100%�� �޼��� ������ ����
		if (type == 2) {
			if (coverage / room_size == 1) {
				break;
			}
		}
	}

	/*
	// ���� ��ġ ����
	for (int i = back_path.size() - 1; i >= 0; i--) {
		map.map[this->x][this->y] = 3;

		this->x += back_path[i].first;
		this->y += back_path[i].second;
		map.map[this->x][this->y] = 2;

		calc_cost += 3;
		time_cost++;

		this->renderMap(map);
	}
	*/
	cout << "��ũ�� Ŀ������ ����Ƚ�� �ҿ�ð�" << endl;

	// �� ũ�� ���
	cout << map_size << " ";

	// û�� ���� ���
	float coverage_rate = ((float)coverage / (float)room_size) * 100;
	cout << coverage_rate << " ";

	// ���� Ƚ�� ���
	cout << calc_cost << " ";

	// �ҿ� �ð� ���
	cout << time_cost << " ";

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
	int room_size = 0; // �� ����(������)

	for (int i = 0; i < map.width; i++)
		for (int j = 0; j < map.height; j++)
			if (map.map[i][j] != 1)
				room_size++;

	int map_size = map.width * map.height;

	// ���� ���
	vector<pair<int, int> > back_path;
	int half_time_limit = time_limit / 2;

	while (true) {
		int dir = rand() % 4;
		int distance = (rand() % max(map.height, map.width)) + 1;
		calc_cost += 2;

		while ((distance-- > 0) && (map.map[this->x + dx[dir]][this->y + dy[dir]] != 1)) {
			map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��

			this->x += dx[dir];
			this->y += dy[dir];
			map.map[this->x][this->y] = 2;

			back_path.push_back({ dx[dir] * (-1), dy[dir] * (-1) });

			calc_cost += 3;
			time_cost++;
			if (type == 1) {
				if (half_time_limit <= time_cost) {
					break;
				}
			}

			// û�� ���� ��� (���� ������ ��)
			this->renderMap(map);
		}

		coverage = 0;

		for (int i = 0; i < map.width; i++)
			for (int j = 0; j < map.height; j++)
				if (map.map[i][j] == 3)
					coverage++;

		// 1�� : �ð������� �ΰ� �˰����� ����
		if (type == 1) {
			if (half_time_limit <= time_cost) {
				break;
			}
		}

		// 2�� : �ð������� �����ʰ� coverage 100%�� �޼��� ������ ����
		if (type == 2) {
			if (coverage / room_size == 1) {
				break;
			}
		}
	}

	// ���� ��ġ ����
	for (int i = back_path.size() - 1; i >= 0; i--) {
		map.map[this->x][this->y] = 3;
		this->x += back_path[i].first;
		this->y += back_path[i].second;
		map.map[this->x][this->y] = 2;

		calc_cost += 3;
		time_cost++;

		this->renderMap(map);
	}

	cout << "��ũ�� Ŀ������ ����Ƚ�� �ҿ�ð�" << endl;

	// �� ũ�� ���
	cout << map_size << " ";

	// û�� ���� ���
	float coverage_rate = ((float)coverage / (float)room_size) * 100;
	cout << coverage_rate << " ";

	// ���� Ƚ�� ���
	cout << calc_cost << " ";

	// �ҿ� �ð� ���
	cout << time_cost << " ";
}

void robot::spinMove(Map map, int type)
{
	for (int i = 0; i < map.width; i++)
	{
		for (int j = 0; j < map.height; j++)
		{
			if (map.map[i][j] == 2)
			{
				this->x = i;
				this->y = j;
			}
		}
	}

	srand((unsigned)time(NULL));


	int map_calc = 0;
	int memory_calc = 0;
	int move_calc = 0;
	int calc_cost = 0;
	//���� �������� ����� ����

	int time_cost = 0; // �ҿ� �ð�
	int time_limit = 100; // �ð� ����(�ܿ� ���͸�)
	int half_time_limit = time_limit / 2;

	int coverage = 0; // û�� ����
	int room_size = 0; // �� ����
	
	int num_blank = 0; //û�� �ȵ� ����

	for (int i = 0; i < map.width; i++)
		for (int j = 0; j < map.height; j++)
		{
			if (map.map[i][j] != 1)
				room_size++;
			if (map.map[i][j] == 0)
				num_blank++;
		}

	int map_size = map.width * map.height;
	int dir;
	enum dirc { DOWN, UP, RIGHT, LEFT };

	dir = LEFT;	//ó�� ���� ���� ����
	

	// ���� ���
	vector<pair<int, int> > back_path;
	

	while (true) {

		while ((map.map[this->x + dx[DOWN]][this->y + dy[DOWN]] != 1) || (map.map[this->x + dx[UP]][this->y + dy[UP]] != 1) ||
			(map.map[this->x + dx[RIGHT]][this->y + dy[RIGHT]] != 1) || (map.map[this->x + dx[LEFT]][this->y + dy[LEFT]] != 1))
		{

			map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��
			map_calc += 1;

			if ((map.map[this->x + dx[LEFT]][this->y + dy[LEFT]] != 1) && (map.map[this->x + dx[LEFT]][this->y + dy[LEFT]] != 3))
			{
				this->x += dx[LEFT];
				this->y += dy[LEFT];
				map.map[this->x][this->y] = 2;
				move_calc += 1;

				back_path.push_back({ dx[LEFT] * (-1), dy[LEFT] * (-1) });
				memory_calc += 1;
			}
			else if ((map.map[this->x + dx[UP]][this->y + dy[UP]] != 1) && (map.map[this->x + dx[UP]][this->y + dy[UP]] != 3))
			{
				this->x += dx[UP];
				this->y += dy[UP];
				map.map[this->x][this->y] = 2;
				move_calc += 1;

				back_path.push_back({ dx[UP] * (-1), dy[UP] * (-1) });
				memory_calc += 1;
			}
			else if ((map.map[this->x + dx[RIGHT]][this->y + dy[RIGHT]] != 1) && (map.map[this->x + dx[RIGHT]][this->y + dy[RIGHT]] != 3))
			{
				this->x += dx[RIGHT];
				this->y += dy[RIGHT];
				map.map[this->x][this->y] = 2;
				move_calc += 1;

				back_path.push_back({ dx[RIGHT] * (-1), dy[RIGHT] * (-1) });
				memory_calc += 1;
			}
			else if ((map.map[this->x + dx[DOWN]][this->y + dy[DOWN]] != 1) && (map.map[this->x + dx[DOWN]][this->y + dy[DOWN]] != 3))
			{
				this->x += dx[DOWN];
				this->y += dy[DOWN];
				map.map[this->x][this->y] = 2;
				move_calc += 1;

				back_path.push_back({ dx[DOWN] * (-1), dy[DOWN] * (-1) });
				memory_calc += 1;
			}
			//����� �� Ȥ�� �̹� û���ߴ� ������ ���, ���� ����� ��������� ��Ʈ��ŷ�Ͽ� �̵�
			else /*if (!((map.map[this->x + dx[DOWN]][this->y + dy[DOWN]] == 0) || (map.map[this->x + dx[UP]][this->y + dy[UP]] == 0) ||
				 (map.map[this->x + dx[RIGHT]][this->y + dy[RIGHT]] == 0) || (map.map[this->x + dx[LEFT]][this->y + dy[LEFT]] == 0)))*/
			{
				int i = back_path.size() - 1;

				this->x += back_path[i].first;
				this->y += back_path[i].second;
				map.map[this->x][this->y] = 2;
				move_calc += 1;

				back_path.pop_back();
				memory_calc += 1;
			}

			calc_cost = map_calc + move_calc + memory_calc;
			time_cost++;

			if (type == 1) {
				if (half_time_limit <= time_cost) {
					break;
				}
			}

			// û�� ���� ��� (���� ������ ��)
			this->renderMap(map);
		}
	}
}