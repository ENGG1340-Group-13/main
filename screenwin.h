#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <termios.h>
#include <unistd.h>

using namespace std;

class ScreenWin
{
private:
    struct termios old_tio, new_tio;
public:
	int screen_width;
	int screen_height;
    
public:
    ScreenWin(); 
    void init();    
    void draw_map(int xpos,int ypos,int linecnt,vector<string> &tmpvec);
    void draw_char(int xpos,int ypos,char tmpicon);
    void EndWin();
};
