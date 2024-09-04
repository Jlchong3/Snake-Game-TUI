#ifndef SNAKE_H
#define SNAKE_H

typedef struct {
    int x;
    int y;
} Vec2;

enum ERROR { INVALID_INPUT = -1 };
enum COLORS { SNAKE_HEAD = 1, SNAKE_BODY1, SNAKE_BODY2, APPLE };

void initWinGame();

void generateRandomApple();
void initColors();
void setupSnakeGame();

int processGameInput();

bool lostGame();
bool isInBody(Vec2 position);
void retryAlert();

void updateSnakeInfo();
void checkEatApple();
void redrawScore();
void redrawWin();

void endGame();

#endif
