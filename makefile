CC = g++
FILES = main.cpp player.cpp board.cpp
OUT_EXE = game

build: $(FILES)
	$(CC) -std=c++11 -o $(OUT_EXE) $(FILES)

clean:
	rm -f *.o core

rebuild: clean build