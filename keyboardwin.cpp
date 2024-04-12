#include "keyboardwin.h"

using namespace std;


KeyboardWin::KeyboardWin() {
    in = 0;
    listening=false;
}

/*等待键盘输入，直到等到有用的键返回*/
void KeyboardWin::get_key() {
    char tmp;   //读取键值，或过滤功能键的第一个返回值
    char tmp2;  //接受功能键
    this->in=0; //清空以往记录 
    while (listening){
        tmp = getchar();     
        if (tmp == '\033'){    //表示读取的是功能键或者方向键，丢掉第一个返回值，读取第二个返回值   
            getchar(); // 忽略第二个字符 '[' 
            switch (tmp2 = getchar()){   //接収功能键返回值          
                case KEY_UP://上 
                    this->in=KEY_UP;
                    break;
                case KEY_DOWN://下 
                    this->in=KEY_DOWN;
                    break;  
                case KEY_LEFT://左
                    this->in=KEY_LEFT;
                    break;
                case KEY_RIGHT://右
                    this->in=KEY_RIGHT;
                    break;
                default:
                    this->in=0; 
            }
        }
        else{   //普通按键，如字母、数字、space，Esc等按键      
            switch (tmp){
                case KEY_SPACE://空格
                    this->in=KEY_SPACE;                 
                    break;
                case KEY_ENTER://Enter
                    this->in=KEY_ENTER;
                    break;
                case KEY_Q://Esc
                    this->in=KEY_Q;
                    break;
                default: 
                    this->in=0;
            }
        }
    }
}

void KeyboardWin::begin_listening(){
    listening = true;
    kbd_thread = std::thread(&KeyboardWin::get_key, this);
    kbd_thread.detach();
}

void KeyboardWin::stop_listening() {
    listening = false;    
}

int KeyboardWin::read_key() {
    if (in != 0) {
        int return_in = in;
        in = 0;
        return return_in;
    } else {
        return 0;
    }
}
