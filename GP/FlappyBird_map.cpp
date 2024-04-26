#include "FlappyBird_map.h"
//define the original map using the defined class "MAP", stored the map information in a vector.
Map::Map(){
    map = {"          XXXXX                    XXXXX                    XXXXX                    XXXXX                    XXXXX          ", 
           "          XXXXX                    XXXXX                    XXXXX                    XXXXX                    XXXXX          ", 
           "          XXXXX                    XXXXX                    XXXXX                    XXXXX                    XXXXX          ", 
           "          XXXXX                                             XXXXX                    XXXXX                    XXXXX          ",
           "          XXXXX                                                                      XXXXX                    XXXXX          ",
           "          XXXXX                                                                      XXXXX                    XXXXX          ",
           "          XXXXX                                                                      XXXXX                    XXXXX          ", 
           "          XXXXX                                                                      XXXXX                    XXXXX          ", 
           "          XXXXX                                                                      XXXXX                    XXXXX          ",
           "          XXXXX                    XXXXX                                             XXXXX                    XXXXX          ", 
           "          XXXXX                    XXXXX                    XXXXX                    XXXXX                    XXXXX          ",
           "          XXXXX                    XXXXX                    XXXXX                    XXXXX                    XXXXX          ", 
           "                                   XXXXX                    XXXXX                    XXXXX                    XXXXX          ", 
           "                                   XXXXX                    XXXXX                    XXXXX                    XXXXX          ",
           "                                   XXXXX                    XXXXX                    XXXXX                    XXXXX          ",
           "                                   XXXXX                    XXXXX                    XXXXX                    XXXXX          ",
           "                                   XXXXX                    XXXXX                                             XXXXX          ",
           "                                   XXXXX                    XXXXX                                             XXXXX          ",
           "          XXXXX                    XXXXX                    XXXXX                                             XXXXX          ",
           "          XXXXX                    XXXXX                    XXXXX                                             XXXXX          ",
           "          XXXXX                    XXXXX                    XXXXX                                             XXXXX          ",
           "          XXXXX                    XXXXX                    XXXXX                                             XXXXX          ",
           "          XXXXX                    XXXXX                    XXXXX                    XXXXX                                   ",
           "          XXXXX                    XXXXX                    XXXXX                    XXXXX                                   ",
           "          XXXXX                    XXXXX                    XXXXX                    XXXXX                                   ",
           "          XXXXX                    XXXXX                    XXXXX                    XXXXX                                   ",
           "          XXXXX                    XXXXX                    XXXXX                    XXXXX                                   ",
           "          XXXXX                    XXXXX                    XXXXX                    XXXXX                                   ",
           "          XXXXX                    XXXXX                    XXXXX                    XXXXX                    XXXXX          ",
           "          XXXXX                    XXXXX                    XXXXX                    XXXXX                    XXXXX          ",};

}

//define the original position of the bird using the defined class "Bird".
Bird::Bird(){
    xpos = 10;
    ypos = 0;
    speed = 1;
}

//the function moves the bird upward or downward. 
//It inputs the direction of the movement, which is represented by 1 or -1. 
//It has no output, but directly change the map.
void Map::move_bird(int jump){
        map[bird.ypos].replace(bird.xpos,5,"     ");
        bird.ypos += jump;
        if(bird.ypos >= map.size()){
            bird.ypos = 0;
        }
        map[bird.ypos].replace(bird.xpos,5,BIRD);
}

//the function judge whether the bird crashes with the obstacles. 
//It inputs the x and y position of the bird and the map of the obstacles.
//It outputs a bool value, true for crash, false for not crash.
bool crash(int xpos,int ypos,vector<string> map){
    if (ypos < 0 || ypos >= map.size()){
        return true;
    }
    for (int i = xpos; i < xpos + 5; ++i){
        if (map[ypos][i] == 'X'){
            return true;
        }
    }
    return false;
}

//this function refreshes the map when it gets to the boundary. Whenever a section of map is passed, it reads a new section of map from random files.
//It takes no input
//It has no output
void Map::refresh_map(){
    srand(time(NULL));
    int filenum = rand() % 5 + 1;
    string filename = "obstacle" + to_string(filenum) + ".txt";
    ifstream fin(filename.c_str());
    if (fin.fail()){
        exit(1);
    }
    for (int i = 0; i < map.size(); ++i){
        map[i] = map[i].substr(25);
        string line;
        getline(fin,line);
        map[i] = map[i] + line;
        map[i].pop_back();
    }
    fin.close();
}

//the function is the main function for this mini game. It moves the map constantly if the player hasn't won and hasn't lost, gets key input from the user, and judging the end of the game.
//It takes key input from the user
//It outputs the game page and end-of-game images.
int Map::move_map(){
    
    //initialize the game status, such as the position of the bird, the obstacles passed (count), the speed of the bird dropping, and the obstacles moving.
    screen.init();
    int count = 0;
    int tmpresult=-1;
    int const bird_x = 15;
    int tmpspeed_obstacle = speed_obstacle;
    int tmpspeed_bird = speed_bird;
    keyboard.begin_listening();

    //the while loop continues until it reaches the breakpoints (crashing or winning)
    while (true){
        if(tmpspeed_obstacle == 0){
            //if a section of obstacles is passed, the map refreshes.
            if (count % 25 == 0){
            refresh_map();
            }
            int map_start = bird_x + (count % 25);
            bird.xpos = map_start;
            move_bird(0);
            screen.draw_partscreen(map_start, SCREEN_width, map.size(), map);
            count++;
            if (count % 3 == 0){
                bird.speed ++;
            }
            tmpspeed_obstacle = speed_obstacle;
        }
        //get key input
        if (keyboard.read_key() == KEY_SPACE){
            bird.speed = -1;
        }
        if(tmpspeed_bird <= 0){
            screen.draw_string(0,bird.ypos, "     ");
            // fly upwards
            if (bird.speed >= 0){
                if (crash(bird.xpos,bird.ypos + 1,map)){
                    tmpresult=0;
                    screen.draw_string(0,0,"Game Over!");
                    break;
                }
                move_bird(1);
            }
            // fly downwrds
            else{
                if (crash(bird.xpos,bird.ypos - 1,map)){
                    tmpresult=0;
                    screen.draw_string(0,0,"Game Over!");
                    break;
                }
                move_bird(-1);
            }
            screen.draw_string(0,bird.ypos, BIRD);
            tmpspeed_bird = speed_bird;
        }
        //passing 10 obstacles and win the game
        if (count > 25 * 10){
            tmpresult=1;
            screen.draw_string(0,0,"Win!");
            break;
        }
        //use the iteration time of the computer to control the speed of the bird and the obstacles.
        tmpspeed_obstacle--;
        tmpspeed_bird -= abs(bird.speed);
        }
        keyboard.stop_listening();
        if (tmpresult == 0)
            screen.draw_lose();
        else if(tmpresult ==1 )
            screen.draw_win();
        screen.EndWin();
        return tmpresult;
}

