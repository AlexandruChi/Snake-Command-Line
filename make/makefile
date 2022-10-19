CC = g++
FLAGS = -Wall
LFLAG = -lncurses

TARGET = Snake
DEP = ../define ../game/game ../Snake/gameBoard
OBJ = ../game/game.o ../Snake/main.o ../Snake/gameBoard.o

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) $(LFLAG) $^ -o $@

%.o: %.cpp $(DEP)
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: clear

clear:
	-rm $(OBJ)
	-rm $(TARGET)
