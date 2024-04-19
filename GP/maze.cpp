#include "maze.h"

using namespace std;

//“障碍物”类的构造函数 
Mem_Obstacle::Mem_Obstacle(){
    this->obstacle_x=0;
    this->obstacle_y=0;
    this->direct_x=1;
    this->direct_y=2;
}

Maze::Maze(){
    mymap.map_x=MAP_POS_X;
    mymap.map_y=MAP_POS_Y;
    mymap.lines=0;
    mymap.map_width=0;
    mywarrior.warrior_x=0;
    mywarrior.warrior_y=0;
    myexit.exit_x=0;
    myexit.exit_y=0;
}

//随机生成障碍物
void Maze::generate_obs(){
    srand(time(NULL));
    int ObstacleCount = 0;
    int i = 0;
    while(ObstacleCount<2){
        int randomRow = rand() % (mymap.lines - 2) + 1;
        int randomCol = rand() % (mymap.map_width - 2) + 1;
        if (mymap.mem_map[randomRow][randomCol] == ' ') {
            mymap.mem_map[randomRow][randomCol] = 'O';
            Mem_Obstacle *a1=new Mem_Obstacle();
            a1->obstacle_x=mymap.map_x+randomCol;
            a1->obstacle_y=mymap.map_y+randomRow;
            myobstacles.push_back(*a1);
            updatechar(randomCol, randomRow, OBSTACLE);
            ObstacleCount++;
        }
    }
}
 
/* 从文件读出地图数据*/
void Maze::mapinitial(){
    ifstream infile;
    string line;
    int count=0;//文件读入行的计数 
    int tmppos=-1;  
    infile.open(MAPFILENAME);
    if (infile.fail()){
        cout << "fail" << endl;
        return;
    }
    //读取文件并拷贝进“内存地图”中 
    while ( getline (infile,line) ){
      mymap.mem_map.push_back(line);
      mymap.map_width=std::max(mymap.map_width,(int)line.length());         
      //检查当前行的字符串中是否有代表warrior 的字符，如果有则初始化对象 
      tmppos=line.find(WARRIOR);      
      if(tmppos>=0){        
        mywarrior.warrior_x=mymap.map_x+tmppos;
        mywarrior.warrior_y=mymap.map_y+count; 
      }
      //检查当前行的字符串中是否有代表“出口” 的字符，如果有则初始化对象 
      tmppos=-1;
      tmppos=line.find(MAP_EXIT);      
      if(tmppos>=0){        
        myexit.exit_x=mymap.map_x+tmppos;
        myexit.exit_y=mymap.map_y+count;            
      }
      //检查当前行的字符串中是否有代表obstacle 的字符，如果有则初始化对象并放入vector 容器中
	  count++;
}     
    infile.close();
    //地图行数赋值
    this->mymap.lines=count;
}

//更新内存子图上指定位置的字符，在控制台屏幕上更新指定位置的字符 
void Maze::updatechar(int xpos,int ypos,char tmpicon){
    mymap.mem_map[ypos-MAP_POS_Y][xpos-MAP_POS_X]=tmpicon; 
    screen.draw_char(xpos,ypos,tmpicon);    
}
int Maze::move_warrior(int keyvalue){
    int x=mywarrior.warrior_x;
    int y=mywarrior.warrior_y;
    int mx=x-MAP_POS_X;
    int my=y-MAP_POS_Y;
    int tmpresult=0;
    //判断沿箭头的方向是否可移动
    switch(keyvalue){
        case KEY_up:
            if(mymap.mem_map[my-1][mx]==' '){//移动方向的下一步是空格
                updatechar(x,y,' '); 
                y--;
                updatechar(x,y,WARRIOR); 
                tmpresult=1;//成功移动 
            }else if(mymap.mem_map[my-1][mx]==MAP_CHAR){//移动方向的下一步是墙
                tmpresult=2;//撞墙不动 
            }else if(mymap.mem_map[my-1][mx]==OBSTACLE){//移动方向的下一步是障碍物
                updatechar(x,y,' '); 
                y--;
                updatechar(x,y,WARRIOR_DIE);            
                tmpresult=3;//牺牲  
            }else if(mymap.mem_map[my-1][mx]==MAP_EXIT){//移动方向的下一步是出口
                updatechar(x,y,' '); 
                y--;
                updatechar(x,y,WARRIOR_OUT);            
                tmpresult=4;//走出迷宫 
            }               
            break;
        case KEY_down:
            if(mymap.mem_map[my+1][mx]==' '){//移动方向的下一步是空格
                updatechar(x,y,' '); 
                y++;
                updatechar(x,y,WARRIOR); 
                tmpresult=1;//成功移动 
            }else if(mymap.mem_map[my+1][mx]==MAP_CHAR){//移动方向的下一步是墙
                tmpresult=2;//撞墙不动 
            }else if(mymap.mem_map[my+1][mx]==OBSTACLE){//移动方向的下一步是障碍物
                updatechar(x,y,' '); 
                y++;
                updatechar(x,y,WARRIOR_DIE);            
                tmpresult=3;//牺牲  
            }else if(mymap.mem_map[my+1][mx]==MAP_EXIT){//移动方向的下一步是出口
                updatechar(x,y,' '); 
                y++;
                updatechar(x,y,WARRIOR_OUT);            
                tmpresult=4;//走出迷宫 
            }
            break;
        case KEY_left:
            if(mymap.mem_map[my][mx-1]==' '){//移动方向的下一步是空格
                updatechar(x,y,' '); 
                x--;
                updatechar(x,y,WARRIOR); 
                tmpresult=1;//成功移动 
            }else if(mymap.mem_map[my][mx-1]==MAP_CHAR){//移动方向的下一步是墙
                tmpresult=2;//撞墙不动 
            }else if(mymap.mem_map[my][mx-1]==OBSTACLE){//移动方向的下一步是障碍物
                updatechar(x,y,' '); 
                x--;
                updatechar(x,y,WARRIOR_DIE);            
                tmpresult=3;//牺牲  
            }else if(mymap.mem_map[my][mx-1]==MAP_EXIT){//移动方向的下一步是出口
                updatechar(x,y,' '); 
                x--;
                updatechar(x,y,WARRIOR_OUT);            
                tmpresult=4;//走出迷宫 
            }
            break;
        case KEY_right:
            if(mymap.mem_map[my][mx+1]==' '){//移动方向的下一步是空格
                updatechar(x,y,' '); 
                x++;
                updatechar(x,y,WARRIOR); 
                tmpresult=1;//成功移动 
            }else if(mymap.mem_map[my][mx+1]==MAP_CHAR){//移动方向的下一步是墙
                tmpresult=2;//撞墙不动 
            }else if(mymap.mem_map[my][mx+1]==OBSTACLE){//移动方向的下一步是障碍物
                updatechar(x,y,' '); 
                x++;
                updatechar(x,y,WARRIOR_DIE);            
                tmpresult=3;//牺牲  
            }else if(mymap.mem_map[my][mx+1]==MAP_EXIT){//移动方向的下一步是出口
                updatechar(x,y,' '); 
                x++;
                updatechar(x,y,WARRIOR_OUT);            
                tmpresult=4;//走出迷宫 
            } 
            break;
    }            
    //记录勇士的新坐标并返回结果 
    mywarrior.warrior_x=x;
    mywarrior.warrior_y=y;
    return tmpresult;       
}

int Maze::move_obstacles(){ 
    int x,y,mx,my,x_direction,y_direction;
    int a[4]={0,1,0,-1};//移动方向数组 
    for(int i=0;i<myobstacles.size();i++ ){
        x=myobstacles[i].obstacle_x;
        y=myobstacles[i].obstacle_y;
        mx=x-MAP_POS_X;
        my=y-MAP_POS_Y;
        //设置在移动方向数组中的坐标       
        x_direction=myobstacles[i].direct_x;
        y_direction=myobstacles[i].direct_y;
        while(true){
            int tmp=0;
            switch(mymap.mem_map[my+a[y_direction]][mx+a[x_direction]]){
                case ' '://前方是空格，可以走 
                    updatechar(x,y,' '); 
                    x=x+a[x_direction];
                    y=y+a[y_direction];
                    updatechar(x,y,OBSTACLE); 
                    tmp=1;//成功移动                    
                    break; 
                case WARRIOR://前方是勇士，勇士被撞死，游戏结束 
                    updatechar(x,y,' '); 
                    x=x+a[x_direction];
                    y=y+a[y_direction];
                    updatechar(x,y,WARRIOR_DIE);
                    tmp=4;//勇士被撞死，游戏结束
                    break;                                      
                case MAP_CHAR://前方是墙，不能走 
                    break;              
                case OBSTACLE://前方是障碍物，不能走 
                    break;
                case MAP_EXIT://前方是出口，不能走 
                    break;          
            } 
            if(tmp==1)
                break;
            if(tmp==4)
                return tmp; 
            //改变在移动方向数组中的坐标 
            x_direction=rand()%4;
            y_direction=(x_direction+1)%4;
        }
        myobstacles[i].obstacle_x=x;
        myobstacles[i].obstacle_y=y;
        myobstacles[i].direct_x=x_direction;
        myobstacles[i].direct_y=y_direction;
    }
    return 0;//出错 
}     

/* 初始化"内存屏幕"*/
void Maze::maze_init(){
    //初始化控制台屏幕 
    screen.init();  
    //读文件获取地图，并画在屏幕上 
    mapinitial();
    screen.draw_map(mymap.map_x,mymap.map_y,mymap.lines,mymap.mem_map);
    screen.draw_char(mywarrior.warrior_x,mywarrior.warrior_y,WARRIOR);
    generate_obs();
    keyboard.begin_listening();
}

/* 游戏的主循环函数*/
void Maze::maze_begin(){
    int quit=0;
    int keyinput=0;
    int tmpspeed=SPEED;//设置障碍物移动速度的控制值 
    while(true){
        //根据键盘输入移动“勇士”或退出读键盘的循环 
        keyinput=keyboard.read_key();
        if (keyinput==KEY_up|keyinput==KEY_down|keyinput==KEY_left|keyinput==KEY_right){
            int tmp=move_warrior(keyinput);
            if(tmp==3||tmp==4)
                quit=1;
        }else if(keyinput==KEY_q){
            quit=1;
        }
        //如果障碍物速度的控制值降到 0，就移动一次所有的障碍物 
        if(--tmpspeed==0){
            int tmp=move_obstacles();           
            tmpspeed=SPEED;//重新设置障碍物速度控制值
            if(tmp==4)
                quit=1;
        }          
        //如果是‘ESC’键，就结束键盘监听的守护线程，并退出循环 
        if(quit){
            keyboard.stop_listening();
            screen.EndWin();
            break;
        }           
    }
}

