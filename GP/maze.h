#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "screenwin.h"
#include "keyboardwin.h"

//define the name of map files.
#define MAPFILENAME1 "map3.txt"
#define MAPFILENAME2 "map4.txt"

//define the name of keys
#define MAP_CHAR 'X'
#define MAP_EXIT 'E'
#define OBSTACLE 'O'
#define WARRIOR 'P'
#define WARRIOR_DIE '!'
#define WARRIOR_OUT '#'

//define the status of map.
#define MAP_POS_X 0
#define MAP_POS_Y 0

//define the name of colors.
#define RED "31m"
#define BLUE "34m"
#define GREEN "32m"
#define DEFAULT_COLOR "0m"

//define the speed
#define SPEED 250000000

//define the struct of map, including the position and vector of the map.
struct Mem_Map{
    int map_x;
    int map_y;
    int lines;
    int map_width;
    vector<string> mem_map;  
};

//define the struct of the player, with x and y positions.
struct Mem_Warrior{
    int warrior_x;
    int warrior_y;
};

//define the struct of the exit, with the x and y positions.
struct Mem_Exit{
    int exit_x;
    int exit_y;
};

//define the class of obstacles, with the positions, directions of the obstacles, and the functions to handle the obstacles.
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
    void updatechar(int xpos,int ypos,char tmpicon, string color);    
public:
    Mem_Map mymap;
    Mem_Warrior mywarrior;
    Mem_Exit myexit;
    vector<Mem_Obstacle> myobstacles;
    ScreenWin screen;
    KeyboardWin keyboard;
public:
    Maze(); 
    void maze_init();   
    int move_warrior(int keyvalue);
                                   
    int move_obstacles();
    void mem_clean();
    int maze_begin();
};



