/*这个类用于在内存中构建一个和屏幕控制台一样大小的"内存屏幕"，存储地图（map）以及闯关者（warrior)
当前的状态，以便和实际的屏幕显示逻辑进行分离。因为屏幕显示逻辑需要有跨平台的不同版本*/
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "screenwin.h"
#include "keyboardwin.h"


#define MAPFILENAME "map3.txt"

#define MAP_CHAR 'X'
#define MAP_EXIT 'E'
#define OBSTACLE 'O'
#define WARRIOR 'P'
#define WARRIOR_DIE '!'
#define WARRIOR_OUT '#'

#define MAP_POS_X 0
#define MAP_POS_Y 0

#define SPEED 250000000

struct Mem_Map{
    int map_x;//地图在屏幕上左上角起始点的横坐标 
    int map_y;//地图在屏幕上左上角起始点的纵坐标
    int lines;//地图图形的行数
    int map_width;//地图的宽度 
    vector<string> mem_map;  
};

struct Mem_Warrior{
    int warrior_x;
    int warrior_y;
};

struct Mem_Exit{
    int exit_x;
    int exit_y;
};

class Mem_Obstacle{
public:
    int obstacle_x;
    int obstacle_y;
    int direct_x,direct_y;
public:
    Mem_Obstacle();
};
 
class Maze
{
private:
    void mapinitial();
	void generate_obs();
    void updatechar(int xpos,int ypos,char tmpicon);    
public:
    Mem_Map mymap;//游戏中的“地图” 
    Mem_Warrior mywarrior;//游戏中的“勇士” 
    Mem_Exit myexit;//游戏中的“出口” 
    vector<Mem_Obstacle> myobstacles;//游戏中的所有“障碍物” 
    ScreenWin screen;//游戏中控制“控制台”显示的对象 
    KeyboardWin keyboard;//游戏中读取键盘输入的对象     
public:
    Maze(); //缺省的构造函数
    void maze_init();   
    int move_warrior(int keyvalue);//根据键盘输入值，在屏幕上移动“勇士”
                                   //返回值：1—移动；2—撞墙未动；3—撞障碍物牺牲；4-走出迷宫 
    int move_obstacles();//在屏幕上自动移动“障碍物”  
    void mem_clean();
    int maze_begin();
};



