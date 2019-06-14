/*Ryan Bridglal, 1-15-12
tank war alter*/


//headers
/////////////////////////////////////////////////////////////////////////




#include “TANKWAR.h”



/////////////////////////////////////////////////////////////////////////
// drawtank function
// construct the tank using drawing functions
/////////////////////////////////////////////////////////////////////////
void drawtank(int num) {
int x = tanks[num].x;
int y = tanks[num].y;
int dir = tanks[num].dir;


//draw tank body and turret
rectfill(screen, x-11, y-11, x+11, y+11, tanks[num].color);
rectfill(screen, x-6, y-6, x+6, y+6, 7);


//draw the treads based on orientation
if (dir == 0 || dir == 2) {
rectfill(screen, x-16, y-16, x-11, y+16, 8);
rectfill(screen, x+11, y-16, x+16, y+16, 8);
  }
  else

  if (dir == 1 || dir == 3) {
  rectfill(screen, x-16, y-16, x+16, y-11, 8);
  rectfill(screen, x-16, y+16, x+16, y+11, 8);
}


//draw the turret based on direction
switch (dir) {
  case 0:
  rectfill(screen, x-1, y, x+1, y-16, 8);break;
  case 1:
  rectfill(screen, x, y-1, x+16, y+1, 8);
  break;
  case 2:
  rectfill(screen, x-1, y, x+1, y+16, 8);
  break;
  case 3:
  rectfill(screen, x, y-1, x-16, y+1, 8);
  break;
  }
}




/////////////////////////////////////////////////////////////////////////
// erasetank function
// erase the tank using rectfill
/////////////////////////////////////////////////////////////////////////
void erasetank(int num) {
}


//calculate box to encompass the tank
int left = tanks[num].x – 17;
int top = tanks[num].y – 17;
int right = tanks[num].x + 17;
int bottom = tanks[num].y + 17;


//erase the tank
rectfill(screen, left, top, right, bottom, 0);




/////////////////////////////////////////////////////////////////////////
// movetank function
// move the tank in the current direction
/////////////////////////////////////////////////////////////////////////
void movetank(int num) {
  int dir = tanks[num].dir;
  int speed = tanks[num].speed;


  //update tank position
  switch(dir) {
    case 0:
    tanks[num].y -=
    break;
    case 1:
    tanks[num].x +=
    break;
    case 2:
    tanks[num].y +=
    break;
    case 3:
    tanks[num].x -=
  }


  based on direction
  speed;
  speed;
  speed;
  speed;


  //keep tank inside the screen
  if (tanks[num].x > SCREEN_W-22) {
    tanks[num].x = SCREEN_W-22;
    tanks[num].speed = 0;
  }

  if (tanks[num].x < 22) {
    tanks[num].x = 22;
    tanks[num].speed = 0;
  }

}


if (tanks[num].y > SCREEN_H-22) {
  tanks[num].y = SCREEN_H-22;
  tanks[num].speed = 0;
}

if (tanks[num].y < 22) {
  tanks[num].y = 22;
  tanks[num].speed = 0;
}



/////////////////////////////////////////////////////////////////////////
// explode function
// display random boxes to simulate an explosion
/////////////////////////////////////////////////////////////////////////
void explode(int num, int x, int y) {
  int n;

  //retrieve location of enemy tank
  int tx = tanks[!num].x;
  int ty = tanks[!num].y;

  //is bullet inside the boundary of the enemy tank?
  if (x > tx-16 && x < tx+16 && y > ty-16 && y < ty+16)
  score(num);

  //draw some random circles for the “explosion”
  for (n = 0; n < 10; n++) {
  rectfill(screen, x-16, y-16, x+16, y+16, rand() % 16);
  rest(1);
  }
}


//clear the area of debris
rectfill(screen, x-16, y-16, x+16, y+16, 0);


/////////////////////////////////////////////////////////////////////////
// updatebullet function
// update the position of a bullet
/////////////////////////////////////////////////////////////////////////
void updatebullet(int num) {
int x = bullets[num].x;
int y = bullets[num].y;

if (bullets[num].alive) {
  //erase bullet
  rect(screen, x-1, y-1, x+1, y+1, 0);

  //move bullet
  bullets[num].x += bullets[num].xspd;
  bullets[num].y += bullets[num].yspd;
  x = bullets[num].x;
  y = bullets[num].y;

  //stay within the screen
  if (x < 5 || x > SCREEN_W-5 || y < 20 || y > SCREEN_H-5) {
  bullets[num].alive = 0;
  return;
  }


  //draw bullet
  x = bullets[num].x;
  y = bullets[num].y;
  rect(screen, x-1, y-1, x+1, y+1, 14);
  
  //look for a hit
  if (getpixel(screen, bullets[num].x, bullets[num].y)) {
  bullets[num].alive = 0;
  explode(num, x, y);
  }
}


  //print the bullet’s position
  textprintf_ex(screen, font, SCREEN_W/2-50, 1, 2, 1, “B1 %-3dx%-3d B2 %-3dx%-3d”,
  bullets[0].x, bullets[0].y,
  bullets[1].x, bullets[1].y);
}



/////////////////////////////////////////////////////////////////////////
// checkpath function
// check to see if a point on the screen is black
/////////////////////////////////////////////////////////////////////////
int checkpath(int x1,int y1,int x2,int y2,int x3,int y3) {
}
if (getpixel(screen, x1, y1) ||
getpixel(screen, x2, y2) ||
getpixel(screen, x3, y3))
return 1;
else
return 0;


/////////////////////////////////////////////////////////////////////////
// clearpath function
// verify that the tank can move in the current direction
/////////////////////////////////////////////////////////////////////////
void clearpath(int num) {

//shortcut vars
int dir = tanks[num].dir;
int speed = tanks[num].speed;
int x = tanks[num].x;
int y = tanks[num].y;
switch(dir) {

//check pixels north
case 0:
if (speed > 0) {
  if (checkpath(x-16, y-20, x, y-20, x+16, y-20))
  tanks[num].speed = 0;
  }
  else

  //if reverse dir, check south
  if (checkpath(x-16, y+20, x, y+20, x+16, y+20))
  tanks[num].speed = 0;
  break;

  //check pixels eastcase 1:
  if (speed > 0)
  {
    if (checkpath(x+20, y-16, x+20, y,
    tanks[num].speed = 0;
  }
  else

//if reverse dir, check west
if (checkpath(x-20, y-16, x-20, y,
tanks[num].speed = 0;
break;

//check pixels south
case 2:
if (speed > 0)
{
if (checkpath(x-16, y+20, x, y+20,
tanks[num].speed = 0;
}
else

//if reverse dir, check north
if (checkpath(x-16, y-20, x, y-20,
tanks[num].speed = 0;
break;

//check pixels west
case 3:
if (speed > 0)
{
if (checkpath(x-20, y-16, x-20, y,
tanks[num].speed = 0;
}
else

//if reverse dir, check east
if (checkpath(x+20, y-16, x+20, y,
tanks[num].speed = 0;
break;
}
x+20, y+16))
x-20, y+16))
x+16, y+20 ))
x+16, y-20))
x-20, y+16))
x+20, y+16))
}



/////////////////////////////////////////////////////////////////////////
// fireweapon function
// configure a bullet’s direction and speed and activate it
/////////////////////////////////////////////////////////////////////////
void fireweapon(int num) {
int x = tanks[num].x;
int y = tanks[num].y;


//ready to fire again?
if (!bullets[num].alive)
{
bullets[num].alive = 1;
//fire bullet in direction tank is facing
switch (tanks[num].dir)
{
//north
case 0:
bullets[num].x = x;
bullets[num].y = y-22;
bullets[num].xspd = 0;
bullets[num].yspd = -BULLETSPEED;
break;
//eastcase 1:
bullets[num].x = x+22;
bullets[num].y = y;
bullets[num].xspd = BULLETSPEED;
bullets[num].yspd = 0;
break;
//south
case 2:
bullets[num].x = x;
bullets[num].y = y+22;
bullets[num].xspd = 0;
bullets[num].yspd = BULLETSPEED;
break;
//west
case 3:
bullets[num].x = x-22;
bullets[num].y = y;
bullets[num].xspd = -BULLETSPEED;
bullets[num].yspd = 0;
}
}
}


/////////////////////////////////////////////////////////////////////////
// forward function
// increase the tank’s speed
/////////////////////////////////////////////////////////////////////////
void forward(int num)
{
  tanks[num].speed++;
  if (tanks[num].speed > MAXSPEED)
  tanks[num].speed = MAXSPEED;
}
/////////////////////////////////////////////////////////////////////////
// backward function
// decrease the tank’s speed
/////////////////////////////////////////////////////////////////////////
void backward(int num)
{
  tanks[num].speed–;
  if (tanks[num].speed < -MAXSPEED)
  tanks[num].speed = -MAXSPEED;
}



/////////////////////////////////////////////////////////////////////////
// turnleft function
// rotate the tank counter-clockwise
/////////////////////////////////////////////////////////////////////////
void turnleft(int num)
{
tanks[num].dir–;
if (tanks[num].dir < 0)
tanks[num].dir = 3;
}




/////////////////////////////////////////////////////////////////////////
// turnright function
// rotate the tank clockwise
/////////////////////////////////////////////////////////////////////////
void turnright(int num)
{
tanks[num].dir++;
if (tanks[num].dir > 3)tanks[num].dir = 0;
}




/////////////////////////////////////////////////////////////////////////
// getinput function
// check for player input keys (2 player support)
/////////////////////////////////////////////////////////////////////////
void getinput() {
//hit ESC to quit
if (key[KEY_ESC])
gameover = 1;
//WASD / SPACE keys control tank 1
if (key[KEY_W])
forward(0);
if (key[KEY_D])
turnright(0);
if (key[KEY_A])
turnleft(0);
if (key[KEY_S])
backward(0);
if (key[KEY_SPACE])
fireweapon(0);
//arrow / ENTER keys control tank 2
if (key[KEY_UP])
forward(1);
if (key[KEY_RIGHT])
turnright(1);
if (key[KEY_DOWN])
backward(1);
if (key[KEY_LEFT])
turnleft(1);
if (key[KEY_ENTER])
fireweapon(1);
//short delay after keypress
rest(10);
}





/////////////////////////////////////////////////////////////////////////
// score function
// add a point to the specified player’s score
/////////////////////////////////////////////////////////////////////////
void score(int player) {
//update score
int points = ++tanks[player].score;
//display score
textprintf_ex(screen, font, SCREEN_W-70*(player+1), 1, BURST, 0, “P%d: %d”, player+1,
points);
}






/////////////////////////////////////////////////////////////////////////
// setuptanks function
// set up the starting condition of each tank
/////////////////////////////////////////////////////////////////////////void setuptanks() {
//player 1
tanks[0].x = 30;
tanks[0].y = 40;
tanks[0].dir = 1;
tanks[0].speed = 0;
tanks[0].color = 4;
tanks[0].score = 0;
}
//player 2
tanks[1].x = SCREEN_W-30;
tanks[1].y = SCREEN_H-30;
tanks[1].dir = 3;
tanks[1].speed = 0;
tanks[1].color = 8;
tanks[1].score = 0;







/////////////////////////////////////////////////////////////////////////
// setupdebris function
// set up the debris on the battlefield
/////////////////////////////////////////////////////////////////////////
void setupdebris() {
int n,x,y,size,color;
//fill the battlefield with random debris
for (n = 0; n < BLOCKS; n++) {
x = BLOCKSIZE + rand() % (SCREEN_W-BLOCKSIZE*2);
y = BLOCKSIZE + rand() % (SCREEN_H-BLOCKSIZE*2);
size = (20 + rand() % BLOCKSIZE)/2;
//color = makecol(rand()%255, rand()%255, rand()%255);
rectfill(screen, x-size, y-size, x+size, y+size, 2);
}
}







/////////////////////////////////////////////////////////////////////////
// setupscreen function
// set up the graphics mode and game screen
/////////////////////////////////////////////////////////////////////////
void setupscreen() {
//set video mode
int ret = set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
if (ret != 0) {
allegro_message(allegro_error);
return;
}
//print title
textprintf_ex(screen, font, 1, 1, BURST, 0, “Ryan Bridglal’s Tank War COLORS – %dx%d”,
SCREEN_W, SCREEN_H);
//draw screen border
rect(screen, 0, 12, SCREEN_W-1, SCREEN_H-1, 4);
rect(screen, 1, 13, SCREEN_W-2, SCREEN_H-2, 4);
}






/////////////////////////////////////////////////////////////////////////
// main function
// start point of the program
/////////////////////////////////////////////////////////////////////////
int main(void) {
  
  
  //initialize everything
  allegro_init(); 
  install_keyboard();
  install_timer();
  srand(time(NULL));
  setupscreen();
  setupdebris();
  setuptanks();

  //game loop
  while(!gameover) {
  
  //erase the tanks
  erasetank(0);
  erasetank(1);
  
  //check for collisions
  clearpath(0);
  clearpath(1);
  
  //move the tanks
  movetank(0);
  movetank(1);
  
  //draw the tanks
  drawtank(0);
  drawtank(1);
  
  //update the bullets  
  updatebullet(0);
  updatebullet(1);
  
  //check for keypresses
  if (keypressed())
  getinput();
  }
  
  //slow the game down (adjust as necessary)
  rest(5);

  //end program
  allegro_exit();
  return 0;
}



END_OF_MAIN()
