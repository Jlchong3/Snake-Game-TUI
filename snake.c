#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>
#include "snake.h"

WINDOW * gameWin;
static int win_max_x, win_max_y;
static int BODYCAPACITY = 256;
static int score;

static Vec2 head;
static Vec2 *body;
static Vec2 apple;

static Vec2 dir;

int main() {

    srand(time(NULL));
    initscr();

    initWinGame();

    getmaxyx(gameWin, win_max_y, win_max_x);

    initColors();

    setupSnakeGame();

    for( ; ; )  {

        if(processGameInput() == INVALID_INPUT)
            continue;

        updateSnakeInfo();

        if (lostGame()){
            retryAlert();
        }

        checkEatApple();

        redrawScore();

        redrawWin();

        usleep(130000);
    }

    return 0;
}

void initWinGame(){

    int win_height = getmaxy(stdscr) - 4;
    int win_width = getmaxx(stdscr) - 4;

    gameWin= newwin(win_height, win_width, 2, 3);

    keypad(gameWin, true);
    nodelay(gameWin, true);
    curs_set(0);
    noecho();

    box(gameWin, 0, 0);
    wrefresh(gameWin);
}

void generateRandomApple(){
    do {
        apple.x = rand() % ((win_max_x / 2) - 2) + 1;
        apple.y = rand() % (win_max_y - 2) + 1;
    } while (isInBody(apple) || (head.x == apple.x && head.y == apple.y));
}

void initColors(){
    start_color();
    use_default_colors();
    init_pair(SNAKE_HEAD, COLOR_YELLOW, -1);
    init_pair(SNAKE_BODY1, COLOR_BLUE, -1);
    init_pair(SNAKE_BODY2, COLOR_CYAN, -1);
    init_pair(APPLE, COLOR_RED, -1);
}

void setupSnakeGame(){
    head.x = (win_max_x / 4);
    head.y = win_max_y / 2;

    body = malloc(BODYCAPACITY * sizeof(Vec2));

    dir.x = 1;
    dir.y = 0;

    score = 0;

    generateRandomApple();
}

int processGameInput(){

    int input = wgetch(gameWin);
    switch (input) {
        case KEY_LEFT:
            if (dir.x != 1 && dir.x != -1) {
                dir.x = -1;
                dir.y = 0;
            }
            return 0;
        case KEY_RIGHT:
            if (dir.x != -1 && dir.x != 1) {
                dir.x = 1;
                dir.y = 0;
            }
            return 0;
        case KEY_UP:
            if (dir.y != 1 && dir.y != -1){
                dir.x = 0;
                dir.y = -1;
            }
            return 0;
        case KEY_DOWN:
            if (dir.y != -1) {
                dir.x = 0;
                dir.y = 1;
            }
            return 0;
        case ERR:
            return 0;
        case 'q':
            endGame();
    }
    return INVALID_INPUT;
}

void updateSnakeInfo(){
    for (int i = score; i > 0; i--)
        body[i] = body[i - 1];

    body[0] = head;

    head.x += dir.x;
    head.y += dir.y;

}

bool lostGame(){
    return isInBody(head)|| head.x == win_max_x / 2|| head.x == 0 ||
           head.y == win_max_y - 1|| head.y == 0;
}

bool isInBody(Vec2 position){
    for(int i = 0; i < score; i++)
        if (body[i].x == position.x && body[i].y == position.y)
            return true;

    return false;
}

void retryAlert(){
    char option;

    int retry_height = win_max_y / 2;
    int retry_width = win_max_x / 2;

    // Calculate the top-left corner coordinates for centering the window
    int start_y = (win_max_y - retry_height) / 2 + 2;
    int start_x = (win_max_x - retry_width) / 2 + 2;

    // Create a centered subwindow for the retry alert
    WINDOW *retry = subwin(gameWin, retry_height, retry_width, start_y, start_x);

    werase(gameWin);

    box(retry, 0, 0);

    mvwprintw(retry, retry_height / 3 - 2 , retry_width / 2 - 5, "Game Over");

    mvwprintw(retry, retry_height - retry_height / 3, retry_width / 3 - 5, "[R]etry");

    mvwprintw(retry, retry_height - retry_height / 3, retry_width - retry_width / 3 - 4, "[Q]uit");

    wrefresh(retry);

    for ( ; ; ){
        option = wgetch(retry);
        switch (option) {
            case 'r': case 'R':
                werase(retry);
                wrefresh(retry);
                delwin(retry);

                initWinGame();
                setupSnakeGame();
                return;

            case 'q': case 'Q':
                endGame();
        }
    }

}

void checkEatApple(){
    if (head.x == apple.x && head.y == apple.y) {
        if (score == BODYCAPACITY) {
            BODYCAPACITY = BODYCAPACITY * 1.5;
            body = realloc(body, BODYCAPACITY * sizeof(Vec2));
        }
        score++;
        generateRandomApple();
    };
}

void redrawScore(){
    mvprintw(1, 4, "Score: %d", score);
    refresh();
}

void redrawWin(){
    werase(gameWin);

    int color[] = { SNAKE_BODY1, SNAKE_BODY2 };

    for (int i = 0; i < score; i++) {
        wattron(gameWin, COLOR_PAIR(color[i % 2]));
        mvwaddch(gameWin, body[i].y, body[i].x * 2, 'o');
        wattroff(gameWin, COLOR_PAIR(color[i % 2]));
    }

    wattron(gameWin, COLOR_PAIR(SNAKE_HEAD));
    mvwaddch(gameWin, head.y, head.x * 2, 'o');
    wattroff(gameWin, COLOR_PAIR(SNAKE_HEAD));

    wattron(gameWin, COLOR_PAIR(APPLE));
    mvwaddch(gameWin, apple.y, apple.x * 2, '@');
    wattroff(gameWin, COLOR_PAIR(APPLE));

    box(gameWin, 0, 0);
}

void endGame(){
    endwin();
    free(body);
    exit(0);
}
