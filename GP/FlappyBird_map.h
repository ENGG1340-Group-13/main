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

class Bird{
    public:
        int xpos;
        int ypos;
        int speed;
    public:
        Bird();
};

class Map{
    public:
        vector<string> map;
    public:
        Map();
        void move_map();
        void refresh_map();
        void move_bird(int jump);
        ScreenWin screen;
        Bird bird;
        KeyboardWin keyboard;

};

