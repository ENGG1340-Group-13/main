FLAGS = -pedantic-errors -std=c++11

screenwin.o: screenwin.cpp screenwin.h
	g++ $(FLAGS) -c $<

keyboardwin.o: keyboardwin.cpp keyboardwin.h
	g++ $(FLAGS) -c $< 

maze.o: maze.cpp maze.h screenwin.h keyboardwin.h 
	g++ $(FLAGS) -c $<

main.o: main.cpp include.h maze.h screenwin.h keyboardwin.h
	g++ $(FLAGS) -I ./local/include -I ./local/include/ncursestw -L ./local/lib -c $<	

main: main.o maze.o keyboardwin.o screenwin.o
	g++ -I ./local/include -I ./local/include/ncursestw -L ./local/lib -o $@ $^ -lncursestw -ldl -pthread

clean:
	rm *.o
	rm main
.PHONY: clean

