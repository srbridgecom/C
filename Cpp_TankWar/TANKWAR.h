//Tank war header, Ryan Bridglal 01/15/2012

#ifndef _TANKWAR_H
#define _TANKWAR_H

#include “allegro.h”


//define some game constants

#define
#define
#define
#define
#define
#define
#define
#define
#define
#define


//set display
MODE GFX_AUTODETECT_WINDOWED
WIDTH 640
HEIGHT 480


BLOCKS 5
BLOCKSIZE 100
MAXSPEED 2
BULLETSPEED 10

//colors
TAN makecol(255,242,169)
CAMO makecol(64,142,66)
BURST makecol(255,189,73)


//define tank structure
struct tagTank {
int x, y, dir, speed, color, score;
} tanks[2];


//define bullet structure
struct tagBullet {
int x, y, alive, xspd, yspd;
} bullets[2];


int gameover = 0;


//function prototypes
void drawtank(int num);void erasetank(int num);
void movetank(int num);
void explode(int num, int x, int y);
void updatebullet(int num);
int checkpath(int x1,int y1,int x2,int y2,int x3,int y3);
void clearpath(int num);
void fireweapon(int num);
void forward(int num);
void backward(int num);
void turnleft(int num);
void turnright(int num);
void getinput();
void setuptanks();
void score(int);
void print(const char *s, int c);
void setupdebris();
void setupscreen();


#endif
