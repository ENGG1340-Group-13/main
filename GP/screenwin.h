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
    void draw_partscreen(int left,int width,int linecnt,vector<string> &tmpvec);
    void draw_char(int xpos,int ypos,char tmpicon, string color);
    void draw_string(int xpos,int ypos,string tmpicon);
    void draw_lose();
    void draw_win();
    void draw_quit();
    void EndWin();
};
