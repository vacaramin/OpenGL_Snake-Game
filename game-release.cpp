#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<string>
#include<unistd.h>
#include<sstream>
#include<cmath>
using namespace std;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}


/*
 * Main Canvas drawing function.h
 * */

int startx = 20,starty = 20;
int *ptrx = &startx;
int *ptry = &starty;
const int maxWidth = 200, maxHieght = 150, bSize = 5;
const int snakeLength = maxHieght * maxWidth;
const int LEFT = 1, RIGHT = 3, UP = 5, DOWN = 2;
int direction;
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
    DrawSquare(snakeBody[0][1], snakeBody[0][2], 5, colors[5]);
    for (int i = 1; i < currentLength; ++i) {
        DrawSquare(snakeBody[i][1], snakeBody[i][2], 5, colors[1]);
   }  
   
}

void pushSnake() {
    for (int i = 0; i < currentLength; ++i) {
        if (snakeBody[i][0] == 1){
            snakeBody[i][1] -= bSize;
            if (snakeBody[i][1] < 0) {
                snakeBody[i][1] = maxWidth; 
            }
        }
        else if(snakeBody[i][0] ==3){
            snakeBody[i][1] += bSize;
            snakeBody[i][1] %= maxWidth;
        }
        else if(snakeBody[i][0] ==2){
            snakeBody[i][2] -= bSize;
            if (snakeBody[i][2] < 0) {
                snakeBody[i][2] = maxHieght - bSize;
            }
        }
        else if(snakeBody[i][0] ==5){
            snakeBody[i][2] += bSize;
            snakeBody[i][2] %= maxHieght;
        }
    }
}

void moveBodyUp(int i) {
    snakeBody[i][2] -= bSize;
    if (snakeBody[i][2] < 0) {
        snakeBody[i][2] = maxHieght - bSize;
    }
    snakeBody[i][0] = UP;
}

void moveBodyDown(int i) {
    snakeBody[i][2] += bSize;
    snakeBody[i][2] %= maxHieght;
    snakeBody[i][0] = DOWN;
}

void moveBodyLeft(int i) {
    snakeBody[i][1] -= bSize;
    if (snakeBody[i][1] < 0) {
        snakeBody[i][1] = maxWidth; 
    }
    snakeBody[i][0] = LEFT;
}

void moveBodyRight(int i) {
    snakeBody[i][1] += bSize;
    snakeBody[i][1] %= maxWidth;  
    snakeBody[i][0] = RIGHT;
}

void moveSnake() {
    for (int i = currentLength; i > 0; i--) {
        int prevMove = i - 1;
        if (snakeBody[prevMove][0] != snakeBody[i][0]) {
            if (snakeBody[prevMove][0] == LEFT){
                moveBodyLeft(i);
            }
            else if(snakeBody[prevMove][0] == RIGHT){
                moveBodyRight(i);
            }
            else if(snakeBody[prevMove][0] == UP){
                moveBodyUp(i);
            }
            else if(snakeBody[prevMove][0] == DOWN){
                moveBodyDown(i);
            }
        }
    }
}

void snakeDirection() {
    if (direction==LEFT){
        // snakeBody[0][1] -= bSize;
        // if (snakeBody[0][1] < 0) {
        //     snakeBody[0][1] = maxWidth; 
        // }
        snakeBody[0][0] = LEFT;
    }
    else if(direction == RIGHT){
        // snakeBody[0][1] += bSize;
        // snakeBody[0][1] %= maxWidth;
        snakeBody[0][0] = RIGHT;
    }
    else if(direction == DOWN){
        // snakeBody[0][2] -= bSize;
        // if (snakeBody[0][2] < 0) {
        //     snakeBody[0][2] = maxHieght - bSize;
        // }
        snakeBody[0][0] = DOWN;
    }
    else if(direction == UP){
        // snakeBody[0][2] += bSize;
        // snakeBody[0][2] %= maxHieght;
        snakeBody[0][0] = UP;
    }
}

void snakeapp(){
    DrawCircle( *ptrx , *ptry , 5 , colors[5]);
    
    for (int i=0; i<maxWidth; i+=5){
        for(int j=0 ; j<maxHieght; j+=5){
            DrawSquare( i , j ,5,colors[10]);  //This will draw a square shape of size 100x100  at x=300 and y=300
        }
    }
    snakeDirection();
    moveSnake();
    pushSnake();
    drawSnake();
    
}

void Display(){
    // set the background color using function glClearColotgr.
    // to change the background play with the red, green and blue values below.
    // Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

    glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
            0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
    
    //DrawSquare( 200 , 200 ,5,colors[10]);  //This will draw a square shape of size 100x100  at x=300 and y=300
    //DrawString( 50, 600, "Here are some are basic shapes", colors[MISTY_ROSE]); // this will print given string at x=50 , y=600
    //DrawString( 50, 570, "You will use these to make your game", colors[MISTY_ROSE]); // this will print given string at x=50 , y=570
    
    snakeapp(); // This will draw a circle at x=200,y=200 of radius 50
	//DrawSquare( *ptrx-10 , *ptry-10 ,5,colors[10]);																									//                    v1( x,y )   v2( x,y )  , v3( x,y ) 
    //DrawTriangle( 300, 50 , 500, 50 , 400 , 250, colors[MISTY_ROSE] );  // Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
    
    //DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
    //DrawLine( 550 , 50 ,  550 , 600 , 20 , colors[MISTY_ROSE] );
     
   glutSwapBuffers(); // do not modify this line..
}
 
/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT   /*GLUT_KEY_LEFT is constant and contains ASCII for 9left arrow key*/) { 
        direction =1;
    } else if (key == GLUT_KEY_RIGHT  /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow kewy*/) {
        direction=3;
    } else if (key == GLUT_KEY_UP) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ {
        direction=5;
    } else if (key == GLUT_KEY_DOWN)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ {
        direction=2;	
    }
    
    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/
     glutPostRedisplay();
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    
    else if (int(key) == 13)
    {  
	}
    
    glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

void Timer(int m) {

// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0 / FPS, Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
    int width = 650, height = 650; // i have set my window size to be 800 x 600
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("OpenGL Snake Game"); // set the title of our game window
    SetCanvasSize(200,200 ); // set the number of pixels...
    
// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
    glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(5.0 / FPS, Timer, 0);

// now handle the control to library and it will call our registered functions when
// it deems necessary...
    emptySnake();
    glutMainLoop();
    return 1;
}
#endif /* Snake Game */

