.ONESHELL:
.EXPORT_ALL_VARIABLES:

TERMINFO =/lib/terminfo

main: main.cpp
	g++ -static -I ./local/include -I ./local/include/ncursestw -L ./local/lib -o main main.cpp mini3.cpp -lncursestw -ldl -pthread
	./main

start:
	TERMINFO = /lib/terminfo
	./main
.PHONY: start

clean:
	rm *.o
	rm main
.PHONY: clean
