#ifndef gameBoard_hpp
#define gameBoard_hpp

struct gameBoard {
    unsigned int x, y, score = 0;
    char **board;
    
    // map used to calculate the direction the end of the tail should move in
    unsigned long long int move = 1;
    unsigned long long int **moveMap;
    
    bool initBoard();
    
    struct {
        unsigned int x, y, size = 1, minSize,  xtail, ytail;
            // minSize = START_SIZE + colected apples
        char head, tail;
        bool increseSize = 0;
    } snake;
    
    bool moveRight();
    bool moveLeft();
    bool moveUp();
    bool moveDown();
    
    // removes last part of the tail when snake is moving
    void deleteTail();
    
    char apple;
    void placeApple();
};

#endif//gameBoard_hpp
