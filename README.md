# VIRUS INVASION
## Menu
1. [Team members](#Team-members-)
2. [How to play](#How-to-play-)
3. [Features emplemented](#Features-emplemented-)
4. [Library Usage](#Library-usage-)

## Team members
[Guo Xinyi](https://github.com/guoxinyicindy)&ensp;&ensp;&ensp;&ensp;&ensp;()

[Leung Ngo Ki](https://github.com/LEUNGNGOKI)&ensp;&ensp;&ensp;&ensp;(3035930826)

[Yang Jiayi](https://github.com/Seaflight4)&ensp;&ensp;&ensp;&ensp;&ensp;()

[Zhao Guandi](https://github.com/Booker-zgd)&ensp;&ensp;()

[Zhu Jiayi](https://github.com/Andreazjy)&ensp;&ensp;&ensp;&ensp;&ensp;&ensp;(3036127713)

## How to play
### Get started
🌟 REMEMBER to run in the terminal!!
just type "make main" and then "make start" as your command and you can start!!

### Demo
[![asciicast]()

### Characters
player: @  
monster1: X  
monster2: G  
monster3: T

### Rules
You are an invading virus. 
To successfully find your way into a human body, you have to get through a series of serious chanllenges.  

You may encounter the physical and chemical barriers. 
The most powerful weapon of them is their mucus traps. 
To get through those traps, you should press the space key to get a fewer higher.  
Remember that if you not press, then you will get falling and the speed is increasing!  

You may then encounter the maze map according to the non-specific innate responses. 
There are several monsters appear randomly in the map, and they also move without any order.  
Please carefully get rid of them and also find your way out!  

Finally, you may turn to the most scaring specific adaptive responses. 
With their special ability of recognizing outsiders, they will immediately clear you out if you cannot pretend to be a member of the body. 
To make yourself a good pretender, you should be able to choose the corresonding protein size that match with the specific immune cells.  

Now, You can get started!!  

🌟Remember, press "Q" on your keyboard if you want to start a new game or quit out.

## Features Emplemented ✅
### Generation of random game sets or events
1. We have random size of romms and random connections between the three rooms in the main map.
2. We have choose random cylinders appear in the end in minigame1.
3. We have random monsters and moving paths generated in minigame2.

### Various data structures for storing game status
1. We have different [structures](https://github.com/ENGG1340-Group-13/main/blob/main/GP/include.h) for storing gamer position, door, game ,level, monster in main game
2. We use [maps and vectors](https://github.com/ENGG1340-Group-13/main/blob/main/GP/mini3.cpp) to store the fragments and answers provided in minigame3.
3. We use [structures and class](https://github.com/ENGG1340-Group-13/main/blob/main/GP/maze.h) to store the map and monsters in minigame2.
4. We use [map](https://github.com/ENGG1340-Group-13/main/blob/main/GP/screenwin.h) to store the map and other status in minigame1.

### Dynamic memory management
1. We use [dynamic arrays](https://github.com/ENGG1340-Group-13/main/blob/main/GP/main.cpp) to make the player move in main game.

### File Input/Output
1. We read the [map](https://github.com/ENGG1340-Group-13/main/blob/main/GP/maze.cpp) file in the minigame2.
2. We randomly input the [obstacles](https://github.com/ENGG1340-Group-13/main/blob/main/GP/FlappyBird_map.cpp) file in the minigame1.

### Program code in multiple files
We divide our different minigames code and also the header files, so we link them together in the [makefile](https://github.com/ENGG1340-Group-13/main/blob/main/GP/makefile).

### Proper Indentation and naming styles
We all make proper indentation in the code, making sure the functions can be operated well.
We also name our variables neat and easy to know what it stands for.

### In-code documantation
We conclude all the necessary explanation to specify what we are doing insode the code.

## Library usage
We put the required folder ["local"](https://github.com/ENGG1340-Group-13/main/tree/main/GP/local) together with our code. Then if you download our code, the required library will be included.
