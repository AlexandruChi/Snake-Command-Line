#include <ncurses.h>
#include <stdlib.h>
#include <iostream>

#include "gameBoard.hpp"
#include "../game/game.hpp"

#include "../define.h"

using namespace std;

int main(void) {
    int scrX, scrY;
    
    gameBoard board;
    
    initscr();
    noecho();
    refresh();
    curs_set(0);
    keypad(stdscr, TRUE);
    
    // init snake
    board.snake.head = SNAKE_HEAD;
    board.snake.tail = SNAKE_TAIL;
    board.snake.minSize = START_SIZE;
    board.apple = APPLE;
    
    scrX = getmaxx(stdscr);
    scrY = getmaxy(stdscr);
    
    board.x = scrX;
    board.y = scrY;
    
    board.y -= 2;
    board.x -= 2;
    
    board.x /= 2;
    
    board.x = min(board.x, board.y);
    board.x = min(board.x, (unsigned int)BORD_MAX);
    board.y = board.x;
    
    if (!board.initBoard()) {
        endwin();
        fprintf(stderr, __NO_MEMORY);
        exit(EXIT_FAILURE);
    }
    
    board.snake.x = board.x / 2;
    board.snake.y = board.y / 2;
    
    runGame(board);
    
    clear();
    
    mvprintw(scrY / 2 - 3, scrX / 4, "GAME OVER");
    mvprintw(scrY / 2, scrX / 4, "score: %d", board.score);
    mvprintw(scrY / 2 + 3, scrX / 4, "press RETURN to exit");
    
    nodelay(stdscr, FALSE);
    
    while (getch() != '\n');
    
    endwin();
    return 0;
}
