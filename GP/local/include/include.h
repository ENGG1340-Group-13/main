#ifndef INCLUDE_H
#define INCLUDE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
using namespace std;

int MAX_WIDTH = 100;
int MAX_HEIGHT = 30;

typedef struct Position {
    int x;
    int y;
} Position;

typedef struct Door
{
    Position position;
    int connected;
} Door;

typedef struct Game
{
    struct Level * levels[10];
    int currentLevel;
} Game;

typedef struct Level
{
    char ** tiles;
    int level;
    int numberOfRooms;
    struct Room ** rooms;
    struct Monster ** monsters;
    int numberOfMonsters;
    struct Player * player;
} Level;

typedef struct Monster
{
    char string[2];
    char symbol;
    int health;
    int attack;
    int speed;
    int defence;
    int pathfinding;
    int alive;
    Position * position;
} Monster;

typedef struct Player
{
    Position * position;
    int health;
    int attack;
    int maxHealth;
    int exp;
} Player;

typedef struct Room
{
    Position position;
    int height;
    int width;

    struct Door ** doors;
    int numberOfDoors;
    // Monster ** monsters;
    // Item ** items;
} Room;

/* game functions */
void render(Game * game);
void gameLoop(Game * game);

/* level/map functions */
void drawLevel(Level * level);
void addMonsters(Level * level);
void moveMonsters(Level * level);
Level * createLevel(int level);
Room ** roomsSetUp();
char ** saveLevelPositions();
void connectDoors(Level * level);
void checkPosition(Position * newPosition, Level * level);

/* menu functions */
void menuLoop();
int mainMenu();

/* monster functions */
Monster * selectMonster(int level);
Monster * createMonster(char symbol, int health, int attack, int pathfinding);
void pathfindingSeek(Position * start, Position * destination);
void pathfindingRandom(Position * position);
Monster * getMonsterAt(Position * position, Monster ** monsters);
void killMonster(Monster * monster);
void drawMonster(Monster * monster);

/* player functions */
Player * playerSetUp();
Position * handleInput(int input, Player * user);
void playerMove(Position * newPosition, Player * user, char ** level);
void drawPlayer(Player * player);

/* room functions */
Room * createRoom(int grid, int numberOfDoors);
int drawRoom(Room * room);
void placePlayer(Room ** rooms, Player * user);
void setStartingPosition(Monster * monster, Room * room);

/* utils functions */
void pathFind(Position * start, Position * end);
void addPositionYX(int ** frontier, int frontierCount, int y, int x);
int check_Position(int y, int x);
int addNeighbors(int ** frontier, int frontierCount, int *** cameFrom, int y, int x);

/* screen functions */
void screenSetUp();
void printGameHub(Level * level);
void combat(Player * player, Monster * monster);
void print_start_page();
void print_intro();
void endGame();
void print_end_page();

#endif