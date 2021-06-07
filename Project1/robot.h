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
    srand((unsigned)time(NULL));

    int map_calc = 0;
    int memory_calc = 0;
    int move_calc = 0;
    int calc_cost = 0;
    //���� �������� ����� ����

    int time_cost = 0; // �ҿ� �ð�
    int time_limit = 100; // �ð� ����(�ܿ� ���͸�)

    int coverage = 0; // û�� ����
    int room_size = 0; // �� ����
    for (int i = 0; i < map.width; i++)
        for (int j = 0; j < map.height; j++)
            if (map.map[i][j] != 1)
                room_size++;
    int map_size = map.width * map.height; //��ü ����


    enum dirc { DOWN, UP, RIGHT, LEFT }; //���� ������

    vector<pair<int, int> > back_path; //��Ʈ��ŷ�� �߰� ���� �޸�

    // �κ� ������ġ ã��
    for (int i = 0; i < map.width; i++)
    {
        for (int j = 0; j < map.height; j++)
        {
            if (map.map[i][j] == 2)
            {
                this->x = i;
                this->y = j;
                break;
            }
        }
    }

    // 1ĭ �̵�
    while (true)
    {
        map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��
        map_calc += 1;

        if (map.map[this->x + dx[LEFT]][this->y + dy[LEFT]] == 0)
        {
            this->x += dx[LEFT];
            this->y += dy[LEFT];
            map.map[this->x][this->y] = 2;
            move_calc += 1;

            back_path.push_back({ dx[LEFT] * (-1), dy[LEFT] * (-1) });
            memory_calc += 1;
        }
        else if (map.map[this->x + dx[UP]][this->y + dy[UP]] == 0)
        {
            this->x += dx[UP];
            this->y += dy[UP];
            map.map[this->x][this->y] = 2;
            move_calc += 1;

            back_path.push_back({ dx[UP] * (-1), dy[UP] * (-1) });
            memory_calc += 1;
        }
        else if (map.map[this->x + dx[RIGHT]][this->y + dy[RIGHT]] == 0)
        {
            this->x += dx[RIGHT];
            this->y += dy[RIGHT];
            map.map[this->x][this->y] = 2;
            move_calc += 1;

            back_path.push_back({ dx[RIGHT] * (-1), dy[RIGHT] * (-1) });
            memory_calc += 1;
        }
        else if (map.map[this->x + dx[DOWN]][this->y + dy[DOWN]] == 0 )
        {
            this->x += dx[DOWN];
            this->y += dy[DOWN];
            map.map[this->x][this->y] = 2;
            move_calc += 1;

            back_path.push_back({ dx[DOWN] * (-1), dy[DOWN] * (-1) });
            memory_calc += 1;
        }
        //����� �� Ȥ�� �̹� û���ߴ� ������ ���,�����ص� ���� ����� ��������� �̵�
        else
        {
            if (back_path.size() > 0)
            {
                int i = back_path.size() - 1;

                this->x += back_path[i].first;
                this->y += back_path[i].second;
                map.map[this->x][this->y] = 2;
                move_calc += 1;

                back_path.pop_back();
                memory_calc += 1;
            }
            else
            {
                map.map[this->x][this->y] = 3;
                map_calc += 1;
            }
        }

        time_cost++;

        // û�� ���� ��� (���� ������ ��)
        this->renderMap(map);       

        // 1�� : �ð������� �ΰ� �˰����� ����
        if (type == 1) {
            if (time_limit <= time_cost) {
                break;
            }
        }

        coverage = 1;
        // Ŀ������ ����
        for (int i = 0; i < map.width; i++)
            for (int j = 0; j < map.height; j++)
                if (map.map[i][j] == 3)
                    coverage++;

        // 2�� : �ð������� �����ʰ� coverage 100%�� �޼��� ������ ����
        if (type == 2) {
            if (coverage / room_size == 1) {
                break;
            }
        }
    }
    

    this->renderMap(map);

    calc_cost = map_calc + move_calc + memory_calc;

    cout << "��ũ�� / Ŀ������ / ����Ƚ�� / �ҿ�ð�" << endl;

    // �� ũ�� ���
    cout << map_size << " \t";

    // û�� ���� ���
    float coverage_rate = ((float)coverage / (float)room_size) * 100;
    cout << coverage_rate << " \t";

    // ���� Ƚ�� ���
    cout << calc_cost << " \t";

    // �ҿ� �ð� ���
    cout << time_cost << " ";
}

void robot::randomMove(Map map, int type)
{
    srand((unsigned)time(NULL));

    int map_calc = 0;
    int memory_calc = 0;
    int move_calc = 0;
    int calc_cost = 0;
    //���� �������� ����� ����

    int time_cost = 0; // �ҿ� �ð�
    int time_limit = 100; // �ð� ����(�ܿ� ���͸�)

    bool endflag = false;

    int coverage = 0; // û�� ����
    int room_size = 0; // �� ����
    for (int i = 0; i < map.width; i++)
        for (int j = 0; j < map.height; j++)
            if (map.map[i][j] != 1)
                room_size++;

    // �κ� ������ġ ã��
    for (int i = 0; i < map.width; i++)
    {
        for (int j = 0; j < map.height; j++)
        {
            if (map.map[i][j] == 2)
            {
                this->x = i;
                this->y = j;
                break;
            }
        }
    }
    int map_size = map.width * map.height; //��ü ����

    while (!endflag) {
        int dir = rand() % 4;
        int distance = (rand() % max(map.height, map.width)) + 1;
        move_calc += 1;

        while ((distance-- > 0) && (map.map[this->x + dx[dir]][this->y + dy[dir]] != 1)) {
            map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��
            map_calc += 1;

            this->x += dx[dir];
            this->y += dy[dir];
            map.map[this->x][this->y] = 2;
            move_calc += 1;

            time_cost++;

            // û�� ���� ��� (���� ������ ��)
            this->renderMap(map);

            // 1�� : �ð������� �ΰ� �˰����� ����
            if (type == 1) {
                if (time_limit <= time_cost) {
                    endflag = true;
                    break;
                }
            }

            coverage = 1;
            // Ŀ������ ����
            for (int i = 0; i < map.width; i++)
                for (int j = 0; j < map.height; j++)
                    if (map.map[i][j] == 3)
                        coverage++;

            // 2�� : �ð������� �����ʰ� coverage 100%�� �޼��� ������ ����
            if (type == 2) {
                if (coverage / room_size == 1) {
                    endflag = true;
                    break;
                }
            }

            
        } 
    }
    
    calc_cost = map_calc + move_calc + memory_calc;

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
    srand((unsigned)time(NULL));

    int map_calc = 0;
    int memory_calc = 0;
    int move_calc = 0;
    int calc_cost = 0;
    //���� �������� ����� ����

    int time_cost = 0; // �ҿ� �ð�
    int time_limit = 100; // �ð� ����(�ܿ� ���͸�) 

    int coverage = 0; // û�� ����
    int room_size = 0; // �� ����
    for (int i = 0; i < map.width; i++)
        for (int j = 0; j < map.height; j++)
            if (map.map[i][j] != 1)
                room_size++;
    int map_size = map.width * map.height; //��ü ����


    enum dirc { DOWN, UP, RIGHT, LEFT}; //���� ������

    bool traceflag = false;
    int dir = UP; //���⼺

    vector<pair<int, int> > back_path; //��Ʈ��ŷ�� �߰� ���� �޸�

    // �κ� ������ġ ã��
    for (int i = 0; i < map.width; i++)
    {
        for (int j = 0; j < map.height; j++)
        {
            if (map.map[i][j] == 2)
            {
                this->x = i;
                this->y = j;
                break;
            }
        }
    }

    while ((map.map[this->x + dx[LEFT]][this->y + dy[LEFT]] != 1))
    {
        map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��
        map_calc += 1;

        this->x += dx[LEFT];
        this->y += dy[LEFT];
        map.map[this->x][this->y] = 2;
        move_calc += 1;
       
        back_path.push_back({ dx[LEFT] * (-1), dy[LEFT] * (-1) });
        memory_calc += 1;

        // û�� ���� ��� (���� ������ ��)
        this->renderMap(map);
        
    }

    dir = UP;

    // 1ĭ �̵�
    while (true)
    {
        map.map[this->x][this->y] = 3; // û�� �Ϸ� ǥ��
        map_calc += 1;
        
        switch (dir)
        {
        case 3: //���ʹ���
            //������ ���� ������
            if ((map.map[this->x + dx[DOWN]][this->y + dy[DOWN]] != 0))
            {
                if (map.map[this->x + dx[LEFT]][this->y + dy[LEFT]] == 0) // #1
                {
                    this->x += dx[LEFT];
                    this->y += dy[LEFT];
                    map.map[this->x][this->y] = 2;
                    move_calc += 1;

                    back_path.push_back({ dx[LEFT] * (-1), dy[LEFT] * (-1) });
                    memory_calc += 1;
                }
                else if (map.map[this->x + dx[UP]][this->y + dy[UP]] == 0) // #2
                {
                    this->x += dx[UP];
                    this->y += dy[UP];
                    map.map[this->x][this->y] = 2;
                    move_calc += 1;

                    dir = UP;

                    back_path.push_back({ dx[UP] * (-1), dy[UP] * (-1) });
                    memory_calc += 1;
                }
                else
                {
                    traceflag = true;
                }

            }
            //���� ������
            else if ((map.map[this->x + 1][this->y + 1] != 0 && map.map[this->x + dx[DOWN]][this->y + dy[DOWN]] == 0)) 
            {
                this->x += dx[DOWN];
                this->y += dy[DOWN];
                map.map[this->x][this->y] = 2;
                move_calc += 1;

                dir = DOWN;

                back_path.push_back({ dx[DOWN] * (-1), dy[DOWN] * (-1) });
                memory_calc += 1;
            }
            break;
        case 1: // ������
            if ((map.map[this->x + dx[LEFT]][this->y + dy[LEFT]] != 0))
            {
                if (map.map[this->x + dx[UP]][this->y + dy[UP]] == 0) // #1
                {
                    this->x += dx[UP];
                    this->y += dy[UP];
                    map.map[this->x][this->y] = 2;
                    move_calc += 1;

                    back_path.push_back({ dx[UP] * (-1), dy[UP] * (-1) });
                    memory_calc += 1;
                }
                else if (map.map[this->x + dx[RIGHT]][this->y + dy[RIGHT]] == 0) // #2
                {
                    this->x += dx[RIGHT];
                    this->y += dy[RIGHT];
                    map.map[this->x][this->y] = 2;
                    move_calc += 1;

                    dir = RIGHT;

                    back_path.push_back({ dx[RIGHT] * (-1), dy[RIGHT] * (-1) });
                    memory_calc += 1;
                }
                else
                    traceflag = true;

            }
            //���� ������
            else if ((map.map[this->x + 1][this->y - 1] != 0 && map.map[this->x + dx[LEFT]][this->y + dy[LEFT]] == 0)) 
            {
                this->x += dx[LEFT];
                this->y += dy[LEFT];
                map.map[this->x][this->y] = 2;
                move_calc += 1;

                dir = LEFT;

                back_path.push_back({ dx[LEFT] * (-1), dy[LEFT] * (-1) });
                memory_calc += 1;
            }
            break;
        case 2: // ������
            if ((map.map[this->x + dx[UP]][this->y + dy[UP]] != 0))
            {
                if (map.map[this->x + dx[RIGHT]][this->y + dy[RIGHT]] == 0) // #1
                {
                    this->x += dx[RIGHT];
                    this->y += dy[RIGHT];
                    map.map[this->x][this->y] = 2;
                    move_calc += 1;

                    back_path.push_back({ dx[UP] * (-1), dy[UP] * (-1) });
                    memory_calc += 1;
                }
                else if (map.map[this->x + dx[DOWN]][this->y + dy[DOWN]] == 0) // #2
                {
                    this->x += dx[DOWN];
                    this->y += dy[DOWN];
                    map.map[this->x][this->y] = 2;
                    move_calc += 1;

                    dir = DOWN;

                    back_path.push_back({ dx[DOWN] * (-1), dy[DOWN] * (-1) });
                    memory_calc += 1;
                }
                else
                    traceflag = true;

            }
            //���� ������
            else if ((map.map[this->x - 1][this->y - 1] != 0 && map.map[this->x + dx[UP]][this->y + dy[UP]] == 0))
            {
                this->x += dx[UP];
                this->y += dy[UP];
                map.map[this->x][this->y] = 2;
                move_calc += 1;

                dir = UP;

                back_path.push_back({ dx[UP] * (-1), dy[UP] * (-1) });
                memory_calc += 1;
            }
            break;
        case 0: // �Ʒ�
            if ((map.map[this->x + dx[RIGHT]][this->y + dy[RIGHT]] != 0))
            {
                if (map.map[this->x + dx[DOWN]][this->y + dy[DOWN]] == 0) // #1
                {
                    this->x += dx[DOWN];
                    this->y += dy[DOWN];
                    map.map[this->x][this->y] = 2;
                    move_calc += 1;

                    back_path.push_back({ dx[DOWN] * (-1), dy[DOWN] * (-1) });
                    memory_calc += 1;
                }
                else if (map.map[this->x + dx[LEFT]][this->y + dy[LEFT]] == 0) // #2
                {
                    this->x += dx[LEFT];
                    this->y += dy[LEFT];
                    map.map[this->x][this->y] = 2;
                    move_calc += 1;

                    dir = LEFT;

                    back_path.push_back({ dx[LEFT] * (-1), dy[LEFT] * (-1) });
                    memory_calc += 1;
                }
                else
                    traceflag = true;

            }
            //���� ������
            else if ((map.map[this->x - 1][this->y + 1] != 0 && map.map[this->x + dx[RIGHT]][this->y + dy[RIGHT]] == 0))
            {
                this->x += dx[RIGHT];
                this->y += dy[RIGHT];
                map.map[this->x][this->y] = 2;
                move_calc += 1;

                dir = RIGHT;

                back_path.push_back({ dx[RIGHT] * (-1), dy[RIGHT] * (-1) });
                memory_calc += 1;
            }
            break;
        }

        if (traceflag == true)
        {
            traceflag = false;
            if (back_path.size() > 0)
            {
                int i = back_path.size() - 1;
                map.map[this->x][this->y] = 3;

                this->x += back_path[i].first;
                this->y += back_path[i].second;
                map.map[this->x][this->y] = 2;
                move_calc += 1;

                switch (back_path[i].first)
                {
                case 1:
                    dir = RIGHT;
                    break;
                case -1:
                    dir = LEFT;
                    break;
                case 0:
                    if (back_path[i].second == 1)
                        dir = UP;
                    else if (back_path[i].second == -1)
                        dir = DOWN;
                    break;

                }

                back_path.pop_back();
                memory_calc += 1;
            }
            else
            {
                map.map[this->x][this->y] = 3;
                map_calc += 1;
            }
        }

        time_cost++;

        // û�� ���� ��� (���� ������ ��)
        this->renderMap(map);
                       
        coverage = 1;

        // Ŀ������ ����
        for (int i = 0; i < map.width; i++)
            for (int j = 0; j < map.height; j++)
                if (map.map[i][j] == 3)
                    coverage++;

        // 1�� : �ð������� �ΰ� �˰����� ����
        if (type == 1) {
            if (coverage / room_size == 1) {
                break;
            }

            if (time_limit <= time_cost) {
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
    
    this->renderMap(map);

    calc_cost = map_calc + move_calc + memory_calc;

    cout << "��ũ�� / Ŀ������ / ����Ƚ�� / �ҿ�ð�" << endl;

    // �� ũ�� ���
    cout << map_size << " \t";

    // û�� ���� ���
    float coverage_rate = ((float)coverage / (float)room_size) * 100;
    cout << coverage_rate << " \t";

    // ���� Ƚ�� ���
    cout << calc_cost << " \t";

    // �ҿ� �ð� ���
    cout << time_cost << " ";
}

    