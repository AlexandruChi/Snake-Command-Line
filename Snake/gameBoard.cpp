#include <time.h>
#include <iostream>

#include "gameBoard.hpp"

#include "../define.h"

bool gameBoard::initBoard() {
    board = new char*[y];
    if (!board) {
        return false;
    }
    for (int i = 0; i < y; i++) {
        board[i] = new char[x];
        if (!board[i]) {
            return false;
        }
    }
    
    moveMap = new unsigned long long*[y];
    if (!moveMap) {
        return false;
    }
    for (int i = 0; i < y; i++) {
        moveMap[i] = new unsigned long long[x];
        if (!moveMap[i]) {
            return false;
        }
    }
    
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            board[i][j] = ' ';
        }
    }
    
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            moveMap[i][j] = 0;
        }
    }
    
    for (int i = 0; i < x; i++) {
        board[0][i] = '!';
        board[x - 1][i] = '!';
        board[i][0] = '!';
        board[i][x - 1] = '!';
    }
    
    snake.x = x / 2;
    snake.y = y / 2;
    snake.xtail = snake.x;
    snake.ytail = snake.y;
    board[snake.y][snake.x] = snake.head;
    
    moveMap[snake.y][snake.x] = move;
    
    return true;
}

bool gameBoard::moveRight() {
    int newX = snake.x + 1, newY = snake.y;
    
    if (board[newY][newX] == '!') {
        newX = 1;
    }
    if (board[newY][newX] == APPLE) {
        snake.increseSize = true;
        snake.minSize++;
    }
    
    if (board[newY][newX] == SNAKE_TAIL) {
        board[snake.y][snake.x] = SNAKE_TAIL;
        board[newY][newX] = SNAKE_HEAD;
        return false;
    }
    
    board[snake.y][snake.x] = SNAKE_TAIL;
    
    snake.x = newX;
    snake.y = newY;
    
    board[snake.y][snake.x] = SNAKE_HEAD;
    move++;
    moveMap[snake.y][snake.x] = move;
    
    return true;
}

bool gameBoard::moveLeft() {
    int newX = snake.x - 1, newY = snake.y;
    
    if (board[newY][newX] == '!') {
        newX = x - 2;
    }
    if (board[newY][newX] == APPLE) {
        snake.increseSize = true;
        snake.minSize++;
    }
    
    if (board[newY][newX] == SNAKE_TAIL) {
        board[snake.y][snake.x] = SNAKE_TAIL;
        board[newY][newX] = SNAKE_HEAD;
        return false;
    }
    
    board[snake.y][snake.x] = SNAKE_TAIL;
    
    snake.x = newX;
    snake.y = newY;
    
    board[snake.y][snake.x] = SNAKE_HEAD;
    move++;
    moveMap[snake.y][snake.x] = move;
    
    return true;
}

bool gameBoard::moveUp() {
    int newX = snake.x, newY = snake.y - 1;
    
    if (board[newY][newX] == '!') {
        newY = y - 2;
    }
    if (board[newY][newX] == APPLE) {
        snake.increseSize = true;
        snake.minSize++;
    }
    
    if (board[newY][newX] == SNAKE_TAIL) {
        board[snake.y][snake.x] = SNAKE_TAIL;
        board[newY][newX] = SNAKE_HEAD;
        return false;
    }
    
    board[snake.y][snake.x] = SNAKE_TAIL;
    
    snake.x = newX;
    snake.y = newY;
    
    board[snake.y][snake.x] = SNAKE_HEAD;
    move++;
    moveMap[snake.y][snake.x] = move;
    
    return true;
}

bool gameBoard::moveDown() {
    int newX = snake.x, newY = snake.y + 1;
    
    if (board[newY][newX] == '!') {
        newY = 1;
    }
    if (board[newY][newX] == APPLE) {
        snake.increseSize = true;
        snake.minSize++;
    }
    
    if (board[newY][newX] == SNAKE_TAIL) {
        board[snake.y][snake.x] = SNAKE_TAIL;
        board[newY][newX] = SNAKE_HEAD;
        return false;
    }
    
    board[snake.y][snake.x] = SNAKE_TAIL;
    
    snake.x = newX;
    snake.y = newY;
    
    board[snake.y][snake.x] = SNAKE_HEAD;
    move++;
    moveMap[snake.y][snake.x] = move;
    
    
    return true;
}

void gameBoard::deleteTail() {
    unsigned long long int curentTail = moveMap[snake.ytail][snake.xtail];
    
    int newX, newY;
    
    if (snake.size == snake.minSize and !snake.increseSize) {
        
        if (board[snake.ytail][snake.xtail] == snake.tail) {
            board[snake.ytail][snake.xtail] = ' ';
        }
        
        moveMap[snake.ytail][snake.xtail] = 0;
        
        // up
        
        newY = snake.ytail - 1;
        if (newY == 0) {
            newY = y - 2;
        }
        
        if (moveMap[newY][snake.xtail] == curentTail + 1) {
            snake.ytail = newY;
            return;
        }
        
        // down
        
        newY = snake.ytail + 1;
        if (newY == y - 1) {
            newY = 1;
        }
        
        if (moveMap[newY][snake.xtail] == curentTail + 1) {
            snake.ytail = newY;
            return;
        }
        
        // left
        
        newX = snake.xtail - 1;
        if (newX == 0) {
            newX = x - 2;
        }
        
        if (moveMap[snake.ytail][newX] == curentTail + 1) {
            snake.xtail = newX;
            return;
        }
        
        // right
        
        newX = snake.xtail + 1;
        if (newX == x - 1) {
            newX = 1;
        }
        
        if (moveMap[snake.ytail][newX] == curentTail + 1) {
            snake.xtail = newX;
            return;
        }
    }
}

void gameBoard::placeApple() {
    unsigned int randX, randY;
    srand((unsigned int)time(0));
    
    do {
        randX = rand() % x - 1;
        randX++;
        randY = rand() % y - 1;
        randY++;
    } while (board[randY][randX] != ' ');
    
    board[randY][randX] = apple;
}
