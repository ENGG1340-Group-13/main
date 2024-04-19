#include "include.h"
#include "maze.h"
#include "FlappyBird_map.h"
#include "mini3.h"

Game game;


int main()
{
	screenSetUp();
  	menuLoop();
	endwin();
	return 0;
}

//check the validity of the player move
void checkPosition(Position * newPosition, Level * level)
{
    switch (mvinch(newPosition->y, newPosition->x))
    {
        case '.':
        case '#':
        case '+':
            playerMove(newPosition, level->player, level->tiles);
            break;

        case 'X':
	{
			endwin();
		    Map mymap;
    		mymap.move_map();
			gameLoop(&game);
    		break;
	}
        case 'G':
        {
			endwin();
            Maze mymaze;
	        mymaze.maze_init();
	        mymaze.maze_begin();
			gameLoop(&game);
            break;
        }
        case 'T':
			endwin();
            mini3();
			gameLoop(&game);
	        break;
        default:
            break;
    }
}

// set up screen parameters
void screenSetUp()
{
	initscr();
	raw();
	noecho();
	keypad(stdscr, true);
	refresh();

    bkgd(COLOR_PAIR(5));
    start_color();
    init_pair(5, COLOR_WHITE, COLOR_WHITE);


    init_pair(0, COLOR_RED, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    for (int i = 0; i < 30; i++)
    {
        attron(COLOR_PAIR(0));

        mvprintw(15,10 + 2 * i, ">>");
        attroff(COLOR_PAIR(0));
        refresh();
        napms(100);
    }
    mvprintw(15,70, " 100 percent");
    refresh();

    napms(1000);

    for (int i = 0; i < 5; i++)
    {
        attron(COLOR_PAIR(i%5));
        print_start_page();
        attroff(COLOR_PAIR(i%5));
        refresh();
        napms(500);
    }

    napms(1000);
    mvprintw(25,35, "Press Enter to Start Game >>>");
    refresh();
    getch();
	clear();
	return;
}

//print game introduction
void print_intro()
{
	clear();
    WINDOW * introwin = newwin(20,90,5,5);
	refresh();

	box(introwin, 0, 0);
	wrefresh(introwin);
	keypad(introwin,true);

	ifstream fin;
	fin.open("introduction.txt");
	
	string line;
	int i = 1;
	while(getline(fin,line))
	{
		mvwprintw(introwin, i, 1, line.c_str());
		wrefresh(introwin);
		napms(1000);
		i++;
	}
	napms(1000);
	mvwprintw(introwin, i, 25, "Please press ENTER to return to menu...");
	wrefresh(introwin);
    fin.close();
	
	int choice = '\0';
	while (true)
	{
		choice = wgetch(introwin);
		if (choice == 10)
		{
            clear();
            refresh();
			return;
		}	
    }
}

//main menuloop
void menuLoop()
{
	int choice = 4;
	game.currentLevel = 0;

	while(true)
	{
		switch(choice)
		{
			case 0: // print introduction
				print_intro();
				break;
			case 1: // start a new game
				game.currentLevel = -1;
                gameLoop(&game);
				break;
			case 2: //continue the current game
                gameLoop(&game);
                break;
            case 3: // end game
				endGame();
                return;
            case 4:
                gameLoop(&game);
                break;
		}
        choice = mainMenu();
	}
}

//main gameloop
void gameLoop(Game * game)
{
    clear();
    refresh();
    timeout(200);
	int ch = '\0';
	Position * newPosition;
	Level * level;

	if (game->currentLevel == 0)
    {
        game->levels[0] = createLevel(1);
        game->currentLevel++;
    }
    if (game->currentLevel == -1)
    {
        free(game->levels[0]);
        game->levels[0] = createLevel(1);
        game->currentLevel = 1;
    }
    level = game->levels[0];

	while (ch != 'q')
	{
		newPosition = handleInput(ch, level->player);
		checkPosition(newPosition, level);
		moveMonsters(level);
		clear();
		drawLevel(level);
		printGameHub(level);
		if (level->player->health <= 0)
		{
			game->currentLevel = 0;
			return;
		}
		ch = getch();
	}
    clear();
    refresh();
}

//print the mainMenu
int mainMenu() 
{
	WINDOW * menuwin = newwin(20,20,5,40);
	refresh();

	box(menuwin, 0, 0);
	wrefresh(menuwin);
	keypad(menuwin,true);

	string choices[4] = {"Introduction", "New Game", "Continue Game", "End Game"};
	int choice;
	int highlight = 0;

	while(true)
	{
		mvwprintw(menuwin, 1, 7, "Menu");
		for(int i = 0; i < 4; i++)
		{
			if(i == highlight)
			wattron(menuwin, A_REVERSE);
			mvwprintw(menuwin, i+3, 1, choices[i].c_str());
			wattroff(menuwin, A_REVERSE);
		}
		choice = wgetch(menuwin);

		switch(choice)
		{
			case KEY_UP:
				highlight--;
				if(highlight == -1)
					highlight = 0;
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight == 4)
					highlight = 3;
				break;
			default:
				break;
		}
		if(choice == 10)
        {
            wclear(menuwin);
            refresh();
            return highlight;
        }		
	}
}

//function to end game
void endGame()
{
    start_color();
    init_pair(0, COLOR_RED, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);

    clear();
    napms(500);

    for (int i = 0; i < 5; i++)
    {
        attron(COLOR_PAIR(i%5));
        print_end_page();
        attroff(COLOR_PAIR(i%5));
        refresh();
        napms(500);
    }

    return;
}

// print the game hub
void printGameHub(Level * level)
{
    mvprintw(1, 105, "Level: %d", level->level);
    mvprintw(3, 105, "Health: %d(%d)", level->player->health, level->player->maxHealth);
    mvprintw(5, 105, "Attack: %d", level->player->attack);
    mvprintw(7, 105,"Exp: %d", level->player->exp);
}

//create the profile of the level, including rooms, players, monsters, and tiles
Level * createLevel(int level)
{
	Level * newLevel;
	newLevel = (Level*)malloc(sizeof(Level));

	newLevel->level = level;
    newLevel->numberOfRooms = 4;
    newLevel->rooms = roomsSetUp();
    connectDoors(newLevel);
    newLevel->tiles = saveLevelPositions();

    newLevel->player = playerSetUp();
    placePlayer(newLevel->rooms, newLevel->player);

    addMonsters(newLevel);

    return newLevel;
}

//allocate memory for rooms and print out rooms on the screen
Room ** roomsSetUp()
{
	int i;
	int numOfRooms = 4;
	Room **rooms;
	rooms = (Room**)malloc(sizeof(Room)*numOfRooms);

	for (i = 0; i < numOfRooms; i++)
	{
		rooms[i] = createRoom(i,2);
		drawRoom(rooms[i]);
	}

	return rooms;
}

//ramdomly generate rooms, including position, size, doors, corridors
Room * createRoom(int grid, int numberOfDoors)
{
    int i;
    Room * newRoom;
    newRoom = (Room *)malloc(sizeof(Room));
    newRoom->numberOfDoors = numberOfDoors;

    switch (grid)
    {
        case 0:
            newRoom->position.x = 0;
            newRoom->position.y = 0;
            break;
        case 1:
            newRoom->position.x = 50;
            newRoom->position.y = 0;
            break;

        case 2:
            newRoom->position.x = 50;
            newRoom->position.y = 15;
            break;
        case 3:
            newRoom->position.x = 0;
            newRoom->position.y = 15;
            break;
    }

    newRoom->height = rand() % 6 + 5; /* max size 10 */
    newRoom->width = rand() % 14 + 11; /* max size 24 */

    /* offset */
    newRoom->position.x += rand() % (50 - newRoom->width) + 1;
    newRoom->position.y += rand() % (15 - newRoom->height) + 1;

    newRoom->doors = (Door**)malloc(sizeof(Door *) * numberOfDoors);

    for (i = 0; i < numberOfDoors; i++)
    {
        newRoom->doors[i] = (Door *)malloc(sizeof(Door));
        newRoom->doors[i]->connected = 0;
    }

    newRoom->doors[0]->position.x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
	newRoom->doors[0]->position.y = newRoom->position.y;
	newRoom->doors[1]->position.x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
	newRoom->doors[1]->position.y = newRoom->position.y + newRoom->height - 1;

    return newRoom;
}

// draw rooms on the screen
int drawRoom(Room * room)
{
    int x;
    int y;

    /* draw top and bottom */
    for (x = room->position.x; x < room->position.x + room->width; x++)
    {
        mvprintw(room->position.y, x, "-"); /* top */
        mvprintw(room->position.y + room->height - 1, x, "-"); /* bottom */
    }

    /* draw floors and side walls */
    for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++)
    {
        /* draw side walls */
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");

        /* draw floors */
        for (x = room->position.x + 1; x <room->position.x + room->width - 1; x++)
        {
            mvprintw(y, x, ".");
        }
    }

    /* draw doors */
    mvprintw(room->doors[0]->position.y, room->doors[0]->position.x, "+");
    mvprintw(room->doors[1]->position.y, room->doors[1]->position.x, "+");


    return 1;
}

//find the connecting pathway of doors
void connectDoors(Level * level)
{
	int i;

	for (i = 0; i < level->numberOfRooms; i++)
	{
		pathFind(&level->rooms[(i+1)%4]->doors[0]->position, &level->rooms[i]->doors[1]->position);
	}
}

//save level positions
char ** saveLevelPositions()
{
    int x, y;
    char ** positions;
    positions = (char **)malloc(sizeof(char *) * 40);

    for (y = 0; y < MAX_HEIGHT; y++)
    {
        positions[y] = (char *)malloc(sizeof(char) * 100);
        for (x = 0; x < MAX_WIDTH; x++)
        {
            positions[y][x] = mvinch(y, x) & A_CHARTEXT;
        }
    }
    return positions;
}

//set up the player
Player * playerSetUp()
{
    Player * newPlayer;
    newPlayer = (Player *)malloc(sizeof(Player));
    newPlayer->position = (Position *)malloc(sizeof(Position));

    newPlayer->health = 20;
    newPlayer->maxHealth = 20;
    newPlayer->attack = 20;
    newPlayer->exp = 0;
   
    return newPlayer;
}

//place the player in the room
void placePlayer(Room ** rooms, Player * player)
{
    player->position->x = rooms[3]->position.x + 1;
    player->position->y = rooms[3]->position.y + 1;
}

//add monsters to each room
void addMonsters(Level* level)
{
    int x;
    level->monsters = (Monster**)malloc(sizeof(Monster *)* 3);
    level->numberOfMonsters = 0;

    for (x = 0; x < level->numberOfRooms-1; x++)
    {
        level->monsters[level->numberOfMonsters] = selectMonster(x);
        setStartingPosition(level->monsters[level->numberOfMonsters], level->rooms[x]);
        level->numberOfMonsters++;
    }
}

//set rules for the type of monsters in each room
Monster * selectMonster(int room)
{
    int monster;
    switch (room)
    {
        case 0:
        	return createMonster('X', 2, 1, 1);
        case 1:
        	return createMonster('G', 5, 3, 1);
        case 2:
        	return createMonster('T', 15, 5, 1);
        default:
        	return nullptr;
    }
}

//create the profile for different monsters
Monster * createMonster(char symbol, int health, int attack,int pathfinding)
{
    Monster * newMonster;
    newMonster = (Monster*)malloc(sizeof(Monster));


    newMonster->symbol = symbol;
    newMonster->health = health;
    newMonster->attack = attack;
    newMonster->pathfinding = pathfinding;
    newMonster->alive = 1;

    snprintf(newMonster->string, sizeof(newMonster->string),"%c", symbol);

    newMonster->position = (Position*)malloc(sizeof(Position));

    return newMonster;
}

//randomly place the monsters in the rooms
void setStartingPosition(Monster * monster, Room * room)
{
    monster->position->x = (rand() % (room->width - 2)) + room->position.x + 1;
    monster->position->y = (rand() % (room->height - 2)) + room->position.y + 1;
}

//draw level
void drawLevel(Level * level)
{
	int x, y, i;

	for (y = 0; y < MAX_HEIGHT; y++)
	{
		for (x = 0; x < MAX_WIDTH; x++)
		{
			mvaddch(y, x, level->tiles[y][x]);
		}
	}

	for (i = 0; i < level->numberOfMonsters; i++)
	{
		drawMonster(level->monsters[i]);
	}

	drawPlayer(level->player);
}

void drawPlayer(Player * player)
{
    mvprintw(player->position->y, player->position->x, "@");
    move(player->position->y, player->position->x);
}

void drawMonster(Monster * monster)
{
    if (monster->alive)
    {
        mvprintw(monster->position->y, monster->position->x, monster->string);
    }
}

Position * handleInput(int input, Player * player)
{
    Position * newPosition;
    newPosition = (Position *)malloc(sizeof(Position));
    switch (input)
    {
        /* move up */
        case 'w':
        case 'W':
            newPosition->y = player->position->y - 1;
            newPosition->x = player->position->x;
            break;

        /* move down */
        case 's':
        case 'S':
            newPosition->y = player->position->y + 1;
            newPosition->x = player->position->x;
            break;

        /* move left */
        case 'a':
        case 'A':
            newPosition->y = player->position->y;
            newPosition->x = player->position->x - 1;
            break;

        /* move right */
        case 'd':
        case 'D':
            newPosition->y = player->position->y;
            newPosition->x = player->position->x + 1;
            break;

        default:
            break;
    }
    return newPosition;
}

//set the motion type of different monsters
void moveMonsters(Level * level)
{
    int x;
    for (x = 0; x < level->numberOfMonsters; x++)
    {
        if (level->monsters[x]->alive == 0)
            continue;

        if (level->monsters[x]->pathfinding == 1)
        {
            mvprintw(30,30," pathfinding is random");
            pathfindingRandom(level->monsters[x]->position);
        }
    }
}

//randomly refresh monster positions
void pathfindingRandom(Position * position)
{
    int random;

    random = rand() % 10;

    switch (random)
    {
        /* step up */
        case 0:
            if (mvinch(position->y - 1, position->x) == '.')
            {
                position->y = position->y - 1;
            }
            break;

        /* step down */
        case 1:
            if (mvinch(position->y + 1, position->x) == '.')
            {
                position->y = position->y + 1;
            }
            break;

        /* step left */
        case 2:
            if (mvinch(position->y, position->x - 1) == '.')
            {
                position->x = position->x - 1;
            }
            break;

        /* step right */
        case 3:
            if (mvinch(position->y, position->x + 1) == '.')
            {
                position->x = position->x + 1;
            }
            break;

        /* do nothing */
        default:
            break;

    }
}

void addPositionYX(int ** frontier, int frontierCount, int y, int x)
{
    frontier[frontierCount][0] = y;
    frontier[frontierCount][1] = x;
}


int check_Position(int y, int x)
{
    char temp = mvinch(y, x) & A_CHARTEXT;

    if (temp == '.' || temp == '|' || temp == '-')
        return 0;
    else
        return 1;
}

int addNeighbors(int ** frontier, int frontierCount, int *** cameFrom, int y, int x)
{
    // north
    if (y > 0 && cameFrom[y - 1][x][0] < 0 && check_Position(y - 1, x))
    {
        addPositionYX(frontier, frontierCount, y - 1, x);
        frontierCount++;
        cameFrom[y - 1][x][0] = y;
        cameFrom[y - 1][x][1] = x;
    }

    // south
    if (y < (MAX_HEIGHT - 1) && cameFrom[y + 1][x][0] < 0 && check_Position(y + 1, x))
    {
        addPositionYX(frontier, frontierCount, y + 1, x);
        frontierCount++;
        cameFrom[y + 1][x][0] = y;
        cameFrom[y + 1][x][1] = x;
    }

    // east
    if (x < (MAX_WIDTH - 1) && cameFrom[y][x + 1][0] < 0 && check_Position(y, x + 1))
    {
        addPositionYX(frontier, frontierCount, y, x + 1);
        frontierCount++;
        cameFrom[y][x + 1][0] = y;
        cameFrom[y][x + 1][1] = x;
    }

    // west
    if (x > 0 && cameFrom[y][x - 1][0] < 0 && check_Position(y, x - 1))
    {
        addPositionYX(frontier, frontierCount, y, x - 1);
        frontierCount++;
        cameFrom[y][x - 1][0] = y;
        cameFrom[y][x - 1][1] = x;
    }

    return frontierCount;

}

//a util function to find the shortest pathway from one point to another
void pathFind(Position * start, Position * end)
{
    int i, j;
    int x, y;
    int tempY;
    int ** frontier = (int **)malloc(sizeof(int*) * MAX_HEIGHT * MAX_WIDTH);
    int *** cameFrom = (int ***)malloc(sizeof(int**) * MAX_HEIGHT );

    int frontierIndex = 0;
    int frontierCount = 0;

    for (i = 0; i < MAX_HEIGHT * MAX_WIDTH; i++)
    {
        frontier[i] = (int *)malloc(sizeof(int)*2);
    }

    for (i = 0; i < MAX_HEIGHT; i++)
    {
        cameFrom[i] = (int** )malloc(sizeof(int*)* MAX_WIDTH);
        for (j = 0; j < MAX_WIDTH; j++)
        {
            cameFrom[i][j] = (int* )malloc(sizeof(int)*2);
            cameFrom[i][j][0] = -1;
            cameFrom[i][j][1] = -1;
        }
    }

    // add start to cameFrom
    cameFrom[start->y][start->x][0] = -9;
    cameFrom[start->y][start->x][1] = -9;

    // add start position to frontier
    addPositionYX(frontier, frontierCount, start->y, start->x);
    frontierCount++;


    while (frontierIndex < frontierCount)
    {
        y = frontier[frontierIndex][0];
        x = frontier[frontierIndex][1];

        frontierIndex++;

        if (y == end->y && x == end->x)
        {
            break;
        }

        frontierCount = addNeighbors(frontier, frontierCount, cameFrom, y, x);
    }

    y = end->y;
    x = end->x;

    while (y != start->y || x != start->x)
    {
        tempY = y;
        y = cameFrom[tempY][x][0];
        x = cameFrom[tempY][x][1];
        mvprintw(y, x, "#");
    }
}

void playerMove(Position * newPosition, Player * player, char ** level)
{
    player->position->y = newPosition->y;
    player->position->x = newPosition->x;
}

void print_end_page()
{
    mvprintw(0,0,":>***************************************************************************************************");
    mvprintw(1,0,":                                                                            v:::::.,...,,;:'d:::::::");
    mvprintw(2,0,"::,                                                                                               :*:");
    mvprintw(3,0,"::::::,':                                                                                          *:");
    mvprintw(4,0,":[:.,':::");
    mvprintw(5,0,"Vv:::::.,...,,;:'d:");
    mvprintw(6,0,":>::::/:##########  ##      ###  ######");
    mvprintw(7,0,"::8*::': ##         ###     ##   ##   ##");
    mvprintw(8,0,"::>:::::|##         ## #    ##   ##     ##");
    mvprintw(9,0,";:::cD:  #########  ##  #   ##   ##     ##");
   mvprintw(10,0,"::B::;   ##         ##   #  ##   ##     ##");
   mvprintw(11,0,"{::G:.,::##         ##    # ##   ##    ##");
   mvprintw(12,0,"::::':  ##########  ##     ###   ######"  );
   mvprintw(13,0,":::::|              ");
   mvprintw(14,0,".,::                                     #######     ####     ###      ###   ######### ");
   mvprintw(15,0,":G                                     ##          ##  ##    ## #    # ##   ##  ");
   mvprintw(16,0,":{{:::::<                              ##         ##    ##   ## ##  ## ##   ## ");
   mvprintw(17,0,"::                                     ##  #####  ########   ##  #  #  ##   ######## ");
   mvprintw(18,0,":+{{::::::L>::::{{::                   ##      #  ##    ##   ##   ##   ##   ## ");
   mvprintw(19,0,":Vv:::::.,..                           ##      #  ##    ##   ##        ##   ##     ");
   mvprintw(20,0,":::Vv:::::.,..:                         #######   ##    ##   ##        ##   ######### ");
   mvprintw(21,0,"::::*JI::");
   mvprintw(22,0,"::::<::::{{::::}:{{::::{{::::");
   mvprintw(23,0,"::::<::::{{::::}:{{::::{{::::");
   mvprintw(24,0,"::::<::::{{::::}:{{::::{{::::");
   mvprintw(25,0,":Vv:::::.,..Vv:::::.,..Vv:::::.,..Vv:::::.,..");
   mvprintw(26,0,",*****************************************************************************************************");
}

void print_start_page()
{
    mvprintw(0,0,":>***************************************************************************************************");
    mvprintw(1,0,":                                                                            v:::::.,...,,;:'d:::::::");
    mvprintw(2,0,"::,                                                                                               :*:");
    mvprintw(3,0,"::::::,':                                                                                          *:");
    mvprintw(4,0,":[:.,':::");
    mvprintw(5,0,"Vv:::::.,...,,;:'d:");
    mvprintw(6,0,":>::::/:###     ##");
    mvprintw(7,0,"::8*::':  ##    ##  ####  #####   #   ##   ####");
    mvprintw(8,0,"::>:::::|  ##   ##   ##   #   ##  #   ##  ##   ");
    mvprintw(9,0,";:::cD:     ##  ##   ##   #####   #   ##   ####");
   mvprintw(10,0,"::B::;       ## ##   ##   #  ##   #   ##      ##");
   mvprintw(11,0,"{::G:.,::     ####  ####  #   ##   #####  #####");
   mvprintw(12,0,"::::':");
   mvprintw(13,0,":::::|                   ####   ##    ##  ##   ##  ####      ####   ####   ####   ##    ##");
   mvprintw(14,0,".,::                      ##    # #   ##   #   ##  #  ##    ##       ##   #   ##  # #   ##");
   mvprintw(15,0,":G                        ##    #  #  ##    #  ##  ######    ####    ##   #   ##  #  #  ##");
   mvprintw(16,0,":{{:::::<                 ##    #   # ##     # ##  #    ##      ##   ##   #   ##  #   # ##");
   mvprintw(17,0,"::                       ####   #    ###      ###  #     ##  ####   ####   ####   #    ###");
   mvprintw(18,0,":+{{::::::L>::::{{::");
   mvprintw(19,0,":Vv:::::.,..");
   mvprintw(20,0,":::Vv:::::.,..:");
   mvprintw(21,0,"::::<::::{{::::}:{{::::{{::::");
   mvprintw(22,0,":Vv:::::.,..Vv:::::.,..Vv:::::.,..Vv:::::.,..");
   mvprintw(23,0,",*****************************************************************************************************");
}
