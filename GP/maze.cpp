#include "maze.h"

using namespace std;

//the function that creates the obstacles.
Mem_Obstacle::Mem_Obstacle(){
    this->obstacle_x=0;
    this->obstacle_y=0;
    this->direct_x=1;
    this->direct_y=2;
}

//define the original status of the map by the class "Maze"
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

//randomly generate the obstacles
void Maze::generate_obs(){
    srand(time(NULL));
    int ObstacleCount = 0;
    int i = 0;
    while(ObstacleCount<3){
        int randomRow = rand() % (mymap.lines - 2) + 1;
        int randomCol = rand() % (mymap.map_width - 2) + 1;
        if (mymap.mem_map[randomRow][randomCol] == ' ') {
            mymap.mem_map[randomRow][randomCol] = 'O';
            Mem_Obstacle *a1=new Mem_Obstacle();
            a1->obstacle_x=mymap.map_x+randomCol;
            a1->obstacle_y=mymap.map_y+randomRow;
            myobstacles.push_back(*a1);
            updatechar(randomCol, randomRow, OBSTACLE, RED);
            ObstacleCount++;
        }
    }
}
 
//read the map from the files
void Maze::mapinitial(){
    ifstream infile;
    string line;
    int count=0;
    int tmppos=-1;  
    int file = rand()%2;
    if(file ==0)
        infile.open(MAPFILENAME1);
    else   
        infile.open(MAPFILENAME2);
    if (infile.fail()){
        cout << "fail" << endl;
        return;
    }
    //read the lines of the map and store them to the map.
    while ( getline (infile,line) ){
      mymap.mem_map.push_back(line);
      mymap.map_width=std::max(mymap.map_width,(int)line.length());         
      tmppos=line.find(WARRIOR);      
      if(tmppos>=0){        
        mywarrior.warrior_x=mymap.map_x+tmppos;
        mywarrior.warrior_y=mymap.map_y+count; 
      }
      tmppos=-1;
      tmppos=line.find(MAP_EXIT);      
      if(tmppos>=0){        
        myexit.exit_x=mymap.map_x+tmppos;
        myexit.exit_y=mymap.map_y+count;            
      }
	  count++;
}     
    infile.close();
    this->mymap.lines=count;
}

//the function that refresh the map.
//it outputs the characters on the screen.
void Maze::updatechar(int xpos,int ypos,char tmpicon, string tmpcolor){
    mymap.mem_map[ypos-MAP_POS_Y][xpos-MAP_POS_X]=tmpicon; 
    screen.draw_char(xpos,ypos,tmpicon, tmpcolor);    
}

//the main function that moves the player around with the command of users.
//It gets the key inputs from the users.
//It outputs the map, the player on the screen.
int Maze::move_warrior(int keyvalue){
    int x=mywarrior.warrior_x;
    int y=mywarrior.warrior_y;
    int mx=x-MAP_POS_X;
    int my=y-MAP_POS_Y;
    int tmpresult=0;
    //check if the move is valid with all the moving directions
    switch(keyvalue){
        case KEY_up:
            if(mymap.mem_map[my-1][mx]==' '){
                updatechar(x,y,' ', DEFAULT_COLOR); 
                y--;
                updatechar(x,y,WARRIOR, BLUE); 
                tmpresult=1;
            }else if(mymap.mem_map[my-1][mx]==MAP_CHAR){
                tmpresult=2;
            }else if(mymap.mem_map[my-1][mx]==OBSTACLE){
                updatechar(x,y,' ', DEFAULT_COLOR); 
                y--;
                updatechar(x,y,WARRIOR_DIE, RED);            
                tmpresult=3; 
            }else if(mymap.mem_map[my-1][mx]==MAP_EXIT){
                updatechar(x,y,' ', DEFAULT_COLOR); 
                y--;
                updatechar(x,y,WARRIOR_OUT, GREEN);            
                tmpresult=4;
            }               
            break;
        case KEY_down:
            if(mymap.mem_map[my+1][mx]==' '){
                updatechar(x,y,' ', DEFAULT_COLOR); 
                y++;
                updatechar(x,y,WARRIOR, BLUE); 
                tmpresult=1;
            }else if(mymap.mem_map[my+1][mx]==MAP_CHAR){
                tmpresult=2;
            }else if(mymap.mem_map[my+1][mx]==OBSTACLE){
                updatechar(x,y,' ', DEFAULT_COLOR); 
                y++;
                updatechar(x,y,WARRIOR_DIE, RED);            
                tmpresult=3;  
            }else if(mymap.mem_map[my+1][mx]==MAP_EXIT){
                updatechar(x,y,' ', DEFAULT_COLOR); 
                y++;
                updatechar(x,y,WARRIOR_OUT, GREEN);            
                tmpresult=4;
            }
            break;
        case KEY_left:
            if(mymap.mem_map[my][mx-1]==' '){
                updatechar(x,y,' ', DEFAULT_COLOR); 
                x--;
                updatechar(x,y,WARRIOR, BLUE); 
                tmpresult=1;
            }else if(mymap.mem_map[my][mx-1]==MAP_CHAR){
                tmpresult=2;
            }else if(mymap.mem_map[my][mx-1]==OBSTACLE){
                updatechar(x,y,' ', DEFAULT_COLOR); 
                x--;
                updatechar(x,y,WARRIOR_DIE, RED);            
                tmpresult=3;
            }else if(mymap.mem_map[my][mx-1]==MAP_EXIT){
                updatechar(x,y,' ', DEFAULT_COLOR); 
                x--;
                updatechar(x,y,WARRIOR_OUT, GREEN);            
                tmpresult=4;
            }
            break;
        case KEY_right:
            if(mymap.mem_map[my][mx+1]==' '){
                updatechar(x,y,' ', DEFAULT_COLOR); 
                x++;
                updatechar(x,y,WARRIOR, BLUE); 
                tmpresult=1;
            }else if(mymap.mem_map[my][mx+1]==MAP_CHAR){
                tmpresult=2;
            }else if(mymap.mem_map[my][mx+1]==OBSTACLE){
                updatechar(x,y,' ', DEFAULT_COLOR); 
                x++;
                updatechar(x,y,WARRIOR_DIE, RED);            
                tmpresult=3;
            }else if(mymap.mem_map[my][mx+1]==MAP_EXIT){
                updatechar(x,y,' ', DEFAULT_COLOR); 
                x++;
                updatechar(x,y,WARRIOR_OUT, GREEN);            
                tmpresult=4;
            } 
            break;
    }     
	
    //record the status of the player
    mywarrior.warrior_x=x;
    mywarrior.warrior_y=y;
    return tmpresult;       
}

//the function that moves the obstacles
//it outputs the obstacles on the screen
int Maze::move_obstacles(){ 
    int x,y,mx,my,x_direction,y_direction;
    int a[4]={0,1,0,-1};
    for(int i=0;i<myobstacles.size();i++ ){
        x=myobstacles[i].obstacle_x;
        y=myobstacles[i].obstacle_y;
        mx=x-MAP_POS_X;
        my=y-MAP_POS_Y;
        x_direction=myobstacles[i].direct_x;
        y_direction=myobstacles[i].direct_y;
        int count = 0;
        while(count<20){
            int tmp=0;
            switch(mymap.mem_map[my+a[y_direction]][mx+a[x_direction]]){
                case ' ':
                    updatechar(x,y,' ', DEFAULT_COLOR); 
                    x=x+a[x_direction];
                    y=y+a[y_direction];
                    updatechar(x,y,OBSTACLE, RED); 
                    tmp=1;
                    count ++;                 
                    break; 
                case WARRIOR:
                    updatechar(x,y,' ', DEFAULT_COLOR); 
                    x=x+a[x_direction];
                    y=y+a[y_direction];
                    updatechar(x,y,WARRIOR_DIE, RED);
                    tmp=4;
                    count++;
                    break;                                      
                case MAP_CHAR:
                    count++;
                    break;              
                case OBSTACLE:
                    count++;
                    break;
                case MAP_EXIT:
                    count++;
                    break;          
            } 
            if(tmp==1)
                break;
            if(tmp==4)
                return tmp; 
            x_direction=rand()%4;
            y_direction=(x_direction+1)%4;
        }
        myobstacles[i].obstacle_x=x;
        myobstacles[i].obstacle_y=y;
        myobstacles[i].direct_x=x_direction;
        myobstacles[i].direct_y=y_direction;
    }
    return 0;
}     

//initialize the screen and the map.
void Maze::maze_init(){
    screen.init();  
    mapinitial();
    screen.draw_map(mymap.map_x,mymap.map_y,mymap.lines,mymap.mem_map);
    screen.draw_char(mywarrior.warrior_x,mywarrior.warrior_y,WARRIOR, BLUE);
    screen.draw_char(myexit.exit_x,myexit.exit_y,MAP_EXIT, GREEN);
    generate_obs();
    screen.draw_string(60, 1, "Press q to quit the game" );
    screen.draw_string(60, 2, "Player: P" );
    screen.draw_string(60, 3, "Obstable: O" );
    screen.draw_string(60, 4, "Exist: E" );
    keyboard.begin_listening();
}

//the main function for this mini game. It get key input from the users and move the map and player correspondingly. It also generate the obstacles and check if the player reaches the exit.
int Maze::maze_begin(){
    int quit=0;
    int tmpresult = -1;
    int keyinput=0;
    int tmpspeed=SPEED;
    //remain running unless reaches the breakpoints (winning or losing)
    while(true){
        keyinput=keyboard.read_key();
        if (keyinput==KEY_up|keyinput==KEY_down|keyinput==KEY_left|keyinput==KEY_right){
            int tmp=move_warrior(keyinput);
            if(tmp==3)
            {
                tmpresult=0;
                quit=1;
            }
            else if (tmp==4){
                tmpresult=1;
                quit=1;
            }
        }else if(keyinput==KEY_q){
            tmpresult=2;
            quit=1;
        }
        if(--tmpspeed==0){
            int tmp=move_obstacles();           
            tmpspeed=SPEED;
            if(tmp==4){
                tmpresult=0;
                quit=1;
            }
        }          
        if(quit){
            keyboard.stop_listening();
            if (tmpresult == 0)
                screen.draw_lose();
            else if(tmpresult ==1 )
                screen.draw_win();
            else if (tmpresult == 2)
                screen.draw_quit();
            screen.EndWin();
            break;
        }           
    }
    return tmpresult;
}

