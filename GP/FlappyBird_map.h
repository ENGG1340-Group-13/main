#include <iostream>
#include "keyboardwin.h"
#include "screenwin.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <chrono>
using namespace std;

#define SCREEN_width 80
#define speed_obstacle 125000000
#define speed_bird 125000000
#define BIRD "///o>"

//create the class of Bird, storing the x and y positions and the speed of the bird
class Bird{
    public:
        int xpos;
        int ypos;
        int speed;
    public:
        Bird();
};

//create the class of Map, storing the obstacles and declaring the functions of the game
class Map{
    public:
        vector<string> map;
    public:
        Map();
        int move_map();
        void refresh_map();
        void move_bird(int jump);
        ScreenWin screen;
        Bird bird;
        KeyboardWin keyboard;

};

