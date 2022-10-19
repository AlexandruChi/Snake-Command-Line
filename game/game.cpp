#include <ncurses.h>
#include <string>
#include <time.h>

#include "gameBoard.hpp"

#include "../define.h"

void placeBoard(WINDOW* win, gameBoard& board);

void runGame(gameBoard& board) {
    int X, Y;
    bool sh = 1;
    
    X = getmaxx(stdscr);
    Y = getmaxy(stdscr);
    
    WINDOW *boardWin = newwin(board.y, board.x * 2, Y / 2 - board.y / 2, X / 2 - board.x);
    board.placeApple();
    placeBoard(boardWin, board);
    
    board.board[board.snake.y][board.snake.x] = board.snake.head;
    
    mvprintw(0, getmaxx(stdscr) / 2 - strlen(__MOVE_KEY) / 2, __MOVE_KEY);
    wrefresh(stdscr);
    
    chtype ch = getch(), ch2;
    
    while (ch != KEY_UP and ch != KEY_DOWN and ch != KEY_LEFT and ch != KEY_RIGHT) {
        ch = getch();
    }
    
    /*
    switch (ch) {
        case KEY_UP:
            sh = board.moveUp();
            break;
        case KEY_DOWN:
            sh = board.moveDown();
            break;
        case KEY_LEFT:
            sh = board.moveLeft();
            break;
        case KEY_RIGHT:
            sh = board.moveRight();
            break;
        default:
            sh = false;
            break;
    }
     */
    
    nodelay(stdscr, TRUE);
    
    clock_t t1, t2;
    double t;
    
    while (sh) {
        t1 = clock();
        t = 0;
        
        while (t < DELAY) {
            ch2 = getch();
            switch (ch2) {
                case KEY_UP:
                    if (ch != KEY_DOWN) {
                        ch = KEY_UP;
                    }
                    break;
                case KEY_DOWN:
                    if (ch != KEY_UP) {
                        ch = KEY_DOWN;
                    }
                    break;
                case KEY_LEFT:
                    if (ch != KEY_RIGHT) {
                        ch = KEY_LEFT;
                    }
                    break;
                case KEY_RIGHT:
                    if (ch != KEY_LEFT) {
                        ch = KEY_RIGHT;
                    }
                    break;
                default:
                    break;
            }
            
            t2 = clock() - t1;
            t = (double)t2 / CLOCKS_PER_SEC;
        }
        
        ch2 = getch();
        switch (ch2) {
            case KEY_UP:
                if (ch != KEY_DOWN) {
                    ch = KEY_UP;
                }
                break;
            case KEY_DOWN:
                if (ch != KEY_UP) {
                    ch = KEY_DOWN;
                }
                break;
            case KEY_LEFT:
                if (ch != KEY_RIGHT) {
                    ch = KEY_LEFT;
                }
                break;
            case KEY_RIGHT:
                if (ch != KEY_LEFT) {
                    ch = KEY_RIGHT;
                }
                break;
            default:
                break;
        }
        
        switch (ch) {
            case KEY_UP:
                sh = board.moveUp();
                break;
            case KEY_DOWN:
                sh = board.moveDown();
                break;
            case KEY_LEFT:
                sh = board.moveLeft();
                break;
            case KEY_RIGHT:
                sh = board.moveRight();
                break;
            default:
                sh = false;
                break;
        }
        
        board.deleteTail();
        
        if (board.snake.increseSize) {
            board.snake.increseSize = false;
            board.score++;
            board.placeApple();
        }
        
        if (board.snake.size < board.snake.minSize) {
            board.snake.size++;
        }

        
        placeBoard(boardWin, board);
    }
}

void placeBoard(WINDOW* win, gameBoard& board) {
    wclear(win);
    for (int i = 1; i < board.y - 1; i++) {
        for (int j = 1; j < board.x - 1; j++) {
            mvwprintw(win, i, j * 2, "%c",  board.board[i][j]);
        }
    }
    box(win, 0, 0);
    wrefresh(win);
}
 
