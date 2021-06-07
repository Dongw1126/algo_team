#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include "map.h"

using namespace std;

// 아래, 위, 오른쪽, 왼쪽
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

class robot
{
private:
    int x, y;
public:
    robot();

    // type 1 : 시간 제한을 두고 알고리즘 수행
    // type 2 : 시간제한을 두지않고 coverage 100%를 달성할 때까지 수행
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
    const string a = "■";  //벽
    const string b = "□";  //청소하지 않은공간
    const string c = "◆"; //로봇청소기
    const string d = "▦"; // 청소 완료

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
    //연산 종류별로 계산비용 구분

    int time_cost = 0; // 소요 시간
    int time_limit = 100; // 시간 제한(잔여 배터리)

    int coverage = 0; // 청소 면적
    int room_size = 0; // 방 면적
    for (int i = 0; i < map.width; i++)
        for (int j = 0; j < map.height; j++)
            if (map.map[i][j] != 1)
                room_size++;
    int map_size = map.width * map.height; //전체 면적


    enum dirc { DOWN, UP, RIGHT, LEFT }; //방향 가독성

    vector<pair<int, int> > back_path; //백트래킹용 추가 내장 메모리

    // 로봇 시작위치 찾기
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

    // 1칸 이동
    while (true)
    {
        map.map[this->x][this->y] = 3; // 청소 완료 표시
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
        //사방이 벽 혹은 이미 청소했던 공간일 경우,저장해둔 가장 가까운 빈공간으로 이동
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

        // 청소 과정 출력 (데모 동영상 용)
        this->renderMap(map);       

        // 1번 : 시간제한을 두고 알고리즘을 수행
        if (type == 1) {
            if (time_limit <= time_cost) {
                break;
            }
        }

        coverage = 1;
        // 커버리지 측정
        for (int i = 0; i < map.width; i++)
            for (int j = 0; j < map.height; j++)
                if (map.map[i][j] == 3)
                    coverage++;

        // 2번 : 시간제한을 두지않고 coverage 100%를 달성할 때까지 수행
        if (type == 2) {
            if (coverage / room_size == 1) {
                break;
            }
        }
    }
    

    this->renderMap(map);

    calc_cost = map_calc + move_calc + memory_calc;

    cout << "맵크기 / 커버리지 / 연산횟수 / 소요시간" << endl;

    // 맵 크기 출력
    cout << map_size << " \t";

    // 청소 면적 출력
    float coverage_rate = ((float)coverage / (float)room_size) * 100;
    cout << coverage_rate << " \t";

    // 연산 횟수 출력
    cout << calc_cost << " \t";

    // 소요 시간 출력
    cout << time_cost << " ";
}

void robot::randomMove(Map map, int type)
{
    srand((unsigned)time(NULL));

    int map_calc = 0;
    int memory_calc = 0;
    int move_calc = 0;
    int calc_cost = 0;
    //연산 종류별로 계산비용 구분

    int time_cost = 0; // 소요 시간
    int time_limit = 100; // 시간 제한(잔여 배터리)

    bool endflag = false;

    int coverage = 0; // 청소 면적
    int room_size = 0; // 방 면적
    for (int i = 0; i < map.width; i++)
        for (int j = 0; j < map.height; j++)
            if (map.map[i][j] != 1)
                room_size++;

    // 로봇 시작위치 찾기
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
    int map_size = map.width * map.height; //전체 면적

    while (!endflag) {
        int dir = rand() % 4;
        int distance = (rand() % max(map.height, map.width)) + 1;
        move_calc += 1;

        while ((distance-- > 0) && (map.map[this->x + dx[dir]][this->y + dy[dir]] != 1)) {
            map.map[this->x][this->y] = 3; // 청소 완료 표시
            map_calc += 1;

            this->x += dx[dir];
            this->y += dy[dir];
            map.map[this->x][this->y] = 2;
            move_calc += 1;

            time_cost++;

            // 청소 과정 출력 (데모 동영상 용)
            this->renderMap(map);

            // 1번 : 시간제한을 두고 알고리즘을 수행
            if (type == 1) {
                if (time_limit <= time_cost) {
                    endflag = true;
                    break;
                }
            }

            coverage = 1;
            // 커버리지 측정
            for (int i = 0; i < map.width; i++)
                for (int j = 0; j < map.height; j++)
                    if (map.map[i][j] == 3)
                        coverage++;

            // 2번 : 시간제한을 두지않고 coverage 100%를 달성할 때까지 수행
            if (type == 2) {
                if (coverage / room_size == 1) {
                    endflag = true;
                    break;
                }
            }

            
        } 
    }
    
    calc_cost = map_calc + move_calc + memory_calc;

    cout << "맵크기 커버리지 연산횟수 소요시간" << endl;

    // 맵 크기 출력
    cout << map_size << " ";

    // 청소 면적 출력
    float coverage_rate = ((float)coverage / (float)room_size) * 100;
    cout << coverage_rate << " ";

    // 연산 횟수 출력
    cout << calc_cost << " ";

    // 소요 시간 출력
    cout << time_cost << " ";
}

void robot::spinMove(Map map, int type)
{
    srand((unsigned)time(NULL));

    int map_calc = 0;
    int memory_calc = 0;
    int move_calc = 0;
    int calc_cost = 0;
    //연산 종류별로 계산비용 구분

    int time_cost = 0; // 소요 시간
    int time_limit = 100; // 시간 제한(잔여 배터리) 

    int coverage = 0; // 청소 면적
    int room_size = 0; // 방 면적
    for (int i = 0; i < map.width; i++)
        for (int j = 0; j < map.height; j++)
            if (map.map[i][j] != 1)
                room_size++;
    int map_size = map.width * map.height; //전체 면적


    enum dirc { DOWN, UP, RIGHT, LEFT}; //방향 가독성

    bool traceflag = false;
    int dir = UP; //방향성

    vector<pair<int, int> > back_path; //백트래킹용 추가 내장 메모리

    // 로봇 시작위치 찾기
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
        map.map[this->x][this->y] = 3; // 청소 완료 표시
        map_calc += 1;

        this->x += dx[LEFT];
        this->y += dy[LEFT];
        map.map[this->x][this->y] = 2;
        move_calc += 1;
       
        back_path.push_back({ dx[LEFT] * (-1), dy[LEFT] * (-1) });
        memory_calc += 1;

        // 청소 과정 출력 (데모 동영상 용)
        this->renderMap(map);
        
    }

    dir = UP;

    // 1칸 이동
    while (true)
    {
        map.map[this->x][this->y] = 3; // 청소 완료 표시
        map_calc += 1;
        
        switch (dir)
        {
        case 3: //왼쪽방향
            //좌측에 벽이 있을때
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
            //벽이 없을때
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
        case 1: // 위방향
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
            //벽이 없을때
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
        case 2: // 오른쪽
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
            //벽이 없을때
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
        case 0: // 아래
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
            //벽이 없을때
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

        // 청소 과정 출력 (데모 동영상 용)
        this->renderMap(map);
                       
        coverage = 1;

        // 커버리지 측정
        for (int i = 0; i < map.width; i++)
            for (int j = 0; j < map.height; j++)
                if (map.map[i][j] == 3)
                    coverage++;

        // 1번 : 시간제한을 두고 알고리즘을 수행
        if (type == 1) {
            if (coverage / room_size == 1) {
                break;
            }

            if (time_limit <= time_cost) {
                break;
            }
        }

        

        // 2번 : 시간제한을 두지않고 coverage 100%를 달성할 때까지 수행
        if (type == 2) {
            if (coverage / room_size == 1) {
                break;
            }
        }
    }
    
    this->renderMap(map);

    calc_cost = map_calc + move_calc + memory_calc;

    cout << "맵크기 / 커버리지 / 연산횟수 / 소요시간" << endl;

    // 맵 크기 출력
    cout << map_size << " \t";

    // 청소 면적 출력
    float coverage_rate = ((float)coverage / (float)room_size) * 100;
    cout << coverage_rate << " \t";

    // 연산 횟수 출력
    cout << calc_cost << " \t";

    // 소요 시간 출력
    cout << time_cost << " ";
}

    