.ONESHELL:
.EXPORT_ALL_VARIABLES:

TERMINFO =/lib/terminfo

FLAGS = -pedantic-errors -std=c++11

screenwin.o: screenwin.cpp screenwin.h
	g++ $(FLAGS) -c $<

keyboardwin.o: keyboardwin.cpp keyboardwin.h
	g++ $(FLAGS) -c $< 

maze.o: maze.cpp maze.h screenwin.h keyboardwin.h 
	g++ $(FLAGS) -c $<

FlappyBird_map.o: FlappyBird_map.cpp FlappyBird_map.h
	g++ $(FLAGS) -c $<

main.o: main.cpp include.h maze.h FlappyBird_map.h screenwin.h keyboardwin.h
	g++ $(FLAGS) -I ./local/include -I ./local/include/ncursestw -L ./local/lib -c $<	
 
mini3.o: mini3.cpp mini3.h
	g++ $(FLAGS) -c $<

main: main.o maze.o keyboardwin.o screenwin.o FlappyBird_map.o mini3.o
	g++ -I ./local/include -I ./local/include/ncursestw -L ./local/lib -o $@ $^ -lncursestw -ldl -pthread


start:
	TERMINFO = /lib/terminfo
	./main
.PHONY: start

clean:
	rm *.o
	rm main
.PHONY: clean
