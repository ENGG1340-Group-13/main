#pragma once

#include <stdio.h>
#include <thread>

using namespace std;

#define KEY_UP 'A'
#define KEY_DOWN 'B'
#define KEY_LEFT 'D'
#define KEY_RIGHT 'C'
#define KEY_SPACE 32
#define KEY_ENTER '\n'
#define KEY_ESC '\033'
#define KEY_Q 'q'
 
class KeyboardWin
{
public:
    int in;
    bool listening;
    thread kbd_thread;
public:
    KeyboardWin();
    void get_key();
    int read_key();
    void begin_listening();
    void stop_listening();
};

