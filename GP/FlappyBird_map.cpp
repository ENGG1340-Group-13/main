#include "FlappyBird_map.h"

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

Bird::Bird(){
    xpos = 10;
    ypos = 0;
    speed = 1;
}

void Map::move_bird(int jump){
        map[bird.ypos].replace(bird.xpos,5,"     ");
        bird.ypos += jump;
        if(bird.ypos >= map.size()){
            bird.ypos = 0;
        }
        map[bird.ypos].replace(bird.xpos,5,BIRD);
        //bird.speed = bird.speed + 1;
}

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

void Map::refresh_map(){
    srand(time(NULL));
    int filenum = rand() % 5 + 1;
    string filename = "obstacle" + to_string(filenum) + ".txt";
    ifstream fin(filename.c_str());
    if (fin.fail()){
        exit(1);
    }
    for (int i = 0; i < map.size(); ++i){
        map[i] = map[i].substr(25);//将第一个obstacle删掉
        string line;
        getline(fin,line);
        map[i] = map[i] + line;//在后面加上一个新的obstacle
        map[i].pop_back();
    }
    fin.close();
}

void Map::move_map(){
    int count = 0;
    int const bird_x = 15;
    int tmpspeed_obstacle = speed_obstacle;
    int tmpspeed_bird = speed_bird;
    keyboard.begin_listening();
    screen.init();
    while (true){
        if(tmpspeed_obstacle == 0){
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
        if (keyboard.read_key() == KEY_SPACE){
            bird.speed = -1;
        }
        if(tmpspeed_bird <= 0){
            screen.draw_string(0,bird.ypos, "     ");
            if (bird.speed >= 0){
                if (crash(bird.xpos,bird.ypos + 1,map)){
                    screen.draw_string(0,0,"Game Over!");
                    break;
                }
                move_bird(1);
            }
            else{
                if (crash(bird.xpos,bird.ypos - 1,map)){
                    screen.draw_string(0,0,"Game Over!");
                    break;
                }
                move_bird(-1);
            }
            screen.draw_string(0,bird.ypos, BIRD);
            tmpspeed_bird = speed_bird;
        }
        if (count > 25 * 5){
            screen.draw_string(0,0,"Win!");
            break;
        }
        tmpspeed_obstacle--;
        tmpspeed_bird -= abs(bird.speed);
        }
        keyboard.stop_listening();
        screen.EndWin();
}

