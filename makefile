CC = g++
FILES = main.cpp player.cpp board.cpp
OUT_EXE = minimaxai

build: $(FILES)
	$(CC) -std=c++11 $(FILES) -o $(OUT_EXE)

clean:
	rm -f *.o core

rebuild: clean build