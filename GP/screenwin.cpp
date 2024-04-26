#include "screenwin.h"

using namespace std;

//get the maximum range of the window.
void maxconsolewindow(int &tmpwidth,int &tmpheight){   
    cout<<"\033[9;1t";
}

//set the status of the window
ScreenWin::ScreenWin(){
    screen_width=0;
    screen_height=0;
} 

//initialize the screen output window
void ScreenWin::init(){
    
     // 获取当前终端设置
    tcgetattr(STDIN_FILENO, &old_tio);

    // 复制终端设置
    new_tio = old_tio;

    // 禁用标准输入的缓冲区和回显
    new_tio.c_lflag &= (~ICANON & ~ECHO);

    // 将新终端设置应用到标准输入
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    
}

//draw the maps of the games.
void ScreenWin::draw_map(int xpos,int ypos,int linecnt,vector<string> &tmpvec){
    cout << "\033[2J\033[1;1H";//将起始光标设成1，1
    for (int i=0;i<linecnt;i++){
        cout<<tmpvec[i]<<endl;
    }
}

//draw a specific character on the screen.
void ScreenWin::draw_char(int xpos,int ypos,char tmpicon, string color){
    cout<<"\033["<<color;
    cout<<"\033["<<ypos+1<<";"<<xpos+1<<"H";
    cout<<tmpicon<<endl;
    cout<<"\033[0m"<<endl;
} 

//draw a string on the screen.
void ScreenWin::draw_string(int xpos,int ypos,string tmpicon){
    cout<<"\033["<<ypos+1<<";"<<xpos+1<<"H";
    cout<<tmpicon<<endl;
} 

//draw part of the map on the screen.
void ScreenWin::draw_partscreen(int left,int width,int linecnt,vector<string> &tmpvec){
    cout << "\033[2J\033[1;1H";//将起始光标设成1，1
    for (int y = 0; y < linecnt; y++){
            cout << tmpvec[y].substr(left, width) << endl;
        }
}

//draw the winning image on the screen.
void ScreenWin::draw_win()
{
    cout << "\033[2J\033[1;1H";
    cout << "\033[32m";
    cout <<"$       $  $$$$$  $$    $"<<endl;
    cout <<"$   $   $    $    $ $   $"<<endl;
    cout <<" $ $ $ $     $    $  $  $"<<endl;
    cout <<" $ $ $ $     $    $   $ $"<<endl;
    cout <<"  $   $    $$$$$  $    $$"<<endl;
    cout << "\033[0m"<<endl;
    cout<<"Press Enter to continue"<<endl;
}

//draw the losing image on the screen.
void ScreenWin::draw_lose()
{
    cout << "\033[2J\033[1;1H";
    cout << "\033[31m";
    cout <<"$      $$$$$   $$$$   $$$$$"<<endl;
    cout <<"$      $   $  $       $    "<<endl;
    cout <<"$      $   $   $$$$   $$$$$"<<endl;
    cout <<"$      $   $       $  $    "<<endl;
    cout <<"$$$$$  $$$$$   $$$$   $$$$$"<<endl;
    cout << "\033[0m"<<endl;
    cout<<"Press Enter to continue"<<endl;
}

//draw the quit image on the screen.
void ScreenWin::draw_quit()
{
    cout << "\033[2J\033[1;1H";
    cout << "\033[34m";
    cout <<" $$$    $   $   $$$   $$$$$"<<endl;
    cout <<"$   $   $   $    $      $  "<<endl;
    cout <<"$ $ $   $   $    $      $  "<<endl;
    cout <<"$  $$   $   $    $      $  "<<endl;
    cout <<" $$$$$  $$$$$   $$$     $  "<<endl;
    cout << "\033[0m"<<endl;
    cout<<"Press Enter to continue"<<endl;
}

//stop the screen output.
void ScreenWin::EndWin()
{
    char c;
    c = getchar(); 
    while (c != '\n' && c != EOF) { 
        c = getchar(); 
        } 
    cout << "\033[2J\033[1;1H"<<endl;
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

