#pragma once

#include <stdio.h>
#include <thread>

using namespace std;

#define KEY_up 'A'
#define KEY_down 'B'
#define KEY_left 'D'
#define KEY_right 'C'
#define KEY_SPACE 32
#define KEY_enter '\n'
#define KEY_esc '\033'
#define KEY_q 'q'
 
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

