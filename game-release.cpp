#include "util.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <unistd.h>
#include <sstream>
#include <cmath>
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int startx = 20, starty = 20;
int *ptrx = &startx;
int *ptry = &starty;
const int maxWidth = 200, maxHieght = 150, bSize = 5;
const int snakeLength = maxHieght * maxWidth;
const int LEFT = 1, RIGHT = 3, UP = 5, DOWN = 2;
int direction = RIGHT; // Initially set the direction to RIGHT
int snakeBody[snakeLength][3], currentLength = 5;

void emptySnake() {
    int sx = 25, sy = 25;
    for (int i = 0; i < 5; ++i) {
        snakeBody[i][0] = 3;
        snakeBody[i][1] = sx;
        snakeBody[i][2] = sy;
        sx -= 5;
    }
    for (int i = 5; i < snakeLength; ++i) {
        snakeBody[i][0] = 0;
        snakeBody[i][1] = 0;
        snakeBody[i][2] = 0;
    }
}

void drawSnake() {
    // Draw head
    DrawSquare(snakeBody[0][1], snakeBody[0][2], 5, colors[5]);
    
    // Draw rest of the body
    for (int i = 1; i < currentLength; ++i) {
        DrawSquare(snakeBody[i][1], snakeBody[i][2], 5, colors[1]);
    }
}


void pushSnake() {
    for (int i = currentLength; i > 0; --i) {
        snakeBody[i][0] = snakeBody[i - 1][0];
        snakeBody[i][1] = snakeBody[i - 1][1];
        snakeBody[i][2] = snakeBody[i - 1][2];
    }
}

void moveSnake() {
    if (direction == LEFT) {
        snakeBody[0][1] -= bSize;
        if (snakeBody[0][1] < 0) {
            snakeBody[0][1] = maxWidth - bSize;
        }
    } else if (direction == RIGHT) {
        snakeBody[0][1] += bSize;
        snakeBody[0][1] %= maxWidth;
    } else if (direction == UP) {
        snakeBody[0][2] += bSize; // Change direction to positive to move up
        snakeBody[0][2] %= maxHieght; // Ensure within the canvas
    } else if (direction == DOWN) {
        snakeBody[0][2] -= bSize; // Change direction to negative to move down
        if (snakeBody[0][2] < 0) {
            snakeBody[0][2] = maxHieght - bSize; // Ensure within the canvas
        }
    }
}
void snakeDirection() {
    if (direction == LEFT) {
        snakeBody[0][0] = LEFT;
    } else if (direction == RIGHT) {
        snakeBody[0][0] = RIGHT;
    } else if (direction == DOWN) {
        snakeBody[0][0] = DOWN;
    } else if (direction == UP) {
        snakeBody[0][0] = UP;
    }
}

void drawBoard() {
    for (int i = 0; i < maxWidth; i += 5) {
        for (int j = 0; j < maxHieght; j += 5) {
            DrawSquare(i, j, 5, colors[10]);  //This will draw a square shape of size 100x100  at x=300 and y=300
        }
    }
}

void snakeapp() {
    drawBoard();
    snakeDirection();
    moveSnake();
    pushSnake();
    drawSnake();
}

void Display() {
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    snakeapp();
    glutSwapBuffers();
}

void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        direction = LEFT;
    } else if (key == GLUT_KEY_RIGHT) {
        direction = RIGHT;
    } else if (key == GLUT_KEY_UP) {
        direction = UP;
    } else if (key == GLUT_KEY_DOWN) {
        direction = DOWN;
    }
    glutPostRedisplay();
}

void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC) {
        exit(1);
    }
    if (key == 'R' || key == 'r') {
        // Rotate
    }
    glutPostRedisplay();
}

void Timer(int m) {
    glutPostRedisplay();
    glutTimerFunc(1000.0 / FPS, Timer, 0);
}

int main(int argc, char *argv[]) {
    int width = 650, height = 650;
    InitRandomizer();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(width, height);
    glutCreateWindow("OpenGL Snake Game");
    SetCanvasSize(200, 200);
    glutDisplayFunc(Display);
    glutSpecialFunc(NonPrintableKeys);
    glutKeyboardFunc(PrintableKeys);
    emptySnake();

    // Set direction to right initially
    direction = RIGHT;

    // Start the timer
    glutTimerFunc(1000.0 / FPS, Timer, 0);

    glutMainLoop();
    return 1;
}
