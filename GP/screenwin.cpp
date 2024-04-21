#include "screenwin.h"

using namespace std;

/*获取控制台最大坐标，并将窗口最大化显示*/
void maxconsolewindow(int &tmpwidth,int &tmpheight){   
    cout<<"\033[9;1t";
}

ScreenWin::ScreenWin(){
    screen_width=0;
    screen_height=0;
} 

/*初始化控制台屏幕*/ 
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

/*在屏幕中画出地图*/ 
void ScreenWin::draw_map(int xpos,int ypos,int linecnt,vector<string> &tmpvec){
    cout << "\033[2J\033[1;1H";//将起始光标设成1，1
    for (int i=0;i<linecnt;i++){
        cout<<tmpvec[i]<<endl;
    }
}
/*在屏幕中指定位置画出一个字符*/
void ScreenWin::draw_char(int xpos,int ypos,char tmpicon, string color){
    cout<<"\033["<<color;
    cout<<"\033["<<ypos+1<<";"<<xpos+1<<"H";
    cout<<tmpicon<<endl;
    cout<<"\033[0m"<<endl;
} 

void ScreenWin::draw_string(int xpos,int ypos,string tmpicon){
    cout<<"\033["<<ypos+1<<";"<<xpos+1<<"H";
    cout<<tmpicon<<endl;
} 

void ScreenWin::draw_partscreen(int left,int width,int linecnt,vector<string> &tmpvec){
    cout << "\033[2J\033[1;1H";//将起始光标设成1，1
    for (int y = 0; y < linecnt; y++){
            cout << tmpvec[y].substr(left, width) << endl;
        }
}

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

