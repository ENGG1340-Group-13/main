#include "keyboardwin.h"

using namespace std;

//initialize the function of handling the key input.
KeyboardWin::KeyboardWin() {
    in = 0;
    listening=false;
}

//wait for the key input until it gets the useful keys.
void KeyboardWin::get_key() {
    char tmp; 
    char tmp2;
    this->in=0; 
    while (listening){
        tmp = getchar();     
        if (tmp == '\033'){    
            getchar(); 
            switch (tmp2 = getchar()){     
                case KEY_up:
                    this->in=KEY_up;
                    break;
                case KEY_down:
                    this->in=KEY_down;
                    break;  
                case KEY_left:
                    this->in=KEY_left;
                    break;
                case KEY_right:
                    this->in=KEY_right;
                    break;
                default:
                    this->in=0; 
            }
        }
        else{     
            switch (tmp){
                case KEY_SPACE:
                    this->in=KEY_SPACE;                 
                    break;
                case KEY_enter:
                    this->in=KEY_enter;
                    break;
                case KEY_q:
                    this->in=KEY_q;
                    break;
                default: 
                    this->in=0;
            }
        }
    }
}

//the function that sets another thread to start getting key input.
void KeyboardWin::begin_listening(){
    listening = true;
    kbd_thread = std::thread(&KeyboardWin::get_key, this);
    kbd_thread.detach();
}

//the function that stops the thread from getting key input.
void KeyboardWin::stop_listening() {
    listening = false;    
}

//the function that actually read the key input.
int KeyboardWin::read_key() {
    if (in != 0) {
        int return_in = in;
        in = 0;
        return return_in;
    } else {
        return 0;
    }
}
