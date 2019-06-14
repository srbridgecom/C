//http://projek.ryanjb.com/games/jumper/
//ryan bridglal
//this is the main file for the game
//


#include "stdio.h"
#include "allegro.h"
#include "mappyal.h"
#include "time.h"

#define MODE GFX_AUTODETECT_WINDOWED
#define WIDTH 640
#define HEIGHT 480
#define JUMPIT 1600
#define RED makecol(100,100,255)

void gameOver();
// define the sprite structure

typedef struct SPRITE {

	int dir, alive, x, y, width, height, xspeed, yspeed;
	int xdelay, ydelay, xcount, ycount;
	int curframe, maxframe, animdelay;
	int framecount, framedelay, facing, enemyFacing;

}

SPRITE;


//POINTERS
// declare the bitmaps and sprites
BITMAP *player_image[8];
SPRITE *player;


BITMAP *title;

//BITMAP *gameOver;

BITMAP *buffer;
BITMAP *temp;

SAMPLE *music;

//SAMPLE *jumpSound;



// tile grabber
BITMAP *grabframe(BITMAP *source, 
	int width, int height,
	int startx, int starty,
	int columns, int frame) {
		BITMAP *temp = create_bitmap(width, height);
		int x = startx + (frame % columns) * width;
		int y = starty + (frame / columns) * height;
		blit(source, temp, x, y, 0, 0, width, height);
		return temp;
}

int collided(int x, int y) {
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
	return blockdata->tl;
}


//Main codee
//
int main(void){

	int mapxoff, mapyoff;
	int oldpy, oldpx;
	int titleX, titleY;
	int facing = 0;
	int jump = JUMPIT;
	int n, VOLUME = 128, PAN = 128, PITCH = 1000;

	//general initialize
	allegro_init();

	install_timer();

	install_keyboard();

	set_color_depth(16);

	set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
	
	set_window_title(" . . .J.U.M.P.E.R. . .     :: Ryan Bridglal ::");


	
	//
	//sound init
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "");

	//load title
	title = load_bitmap("title.bmp", NULL);
	
	//gameOver = load_bitmap("gameover.bmp", NULL);

	// load the player sprite
	temp = load_bitmap("player.bmp", NULL);
	for (n=0; n < 8; n++)
	player_image[n] = grabframe(temp, 50, 64, 0, 0, 8, n);
	destroy_bitmap(temp);


	// load the sound file
	music = load_sample("music.wav");
	
	//jumpSound = load_sample("jump.wav");

	// initialize the sprite
	player = new SPRITE;
	player->x = 80;
	player->y = 100;
	player->curframe = 0;
	player->framecount = 0;
	player->framedelay = 6;
	player->maxframe = 7;
	player->width = player_image[0]->w;
	player->height = player_image[0]->h;


	// load the map
	MapLoad("map.FMP");

	// create the double buffer
	buffer = create_bitmap(WIDTH, HEIGHT);
	clear(buffer);
	
	//always play background music
	play_sample(music, VOLUME, PAN, PITCH, FALSE);



	// main loop
	while(!key[KEY_ESC]) {
		
		oldpy = player->y;
		oldpx = player->x;


		//
		// PLAYER controls
		//
		//right keypress
		if (key[KEY_RIGHT]) {
			clear_to_color(title, makecol(80, 80, 248));
			facing = 1;
			player->x += 2;
			
			if (++player->framecount > player->framedelay) {
				player->framecount = 0;
				
				if (++player->curframe > player->maxframe)
					player->curframe = 1;
			}
		}
		
		
		//left keypress
		else if (key[KEY_LEFT]) {
			clear_to_color(title, makecol(80, 80, 248));
			facing = 0;
			player->x -= 2;
			
			if (++player->framecount > player->framedelay) {
				player->framecount = 0;
				
				if (++player->curframe > player->maxframe)
					player->curframe = 1;
			}
		}
		
		
		else player->curframe = 0;

		// handle jumping
		if (jump == JUMPIT){
		
			if (!collided(player->x + player->width/2, player->y + player->height + 5))
				jump = 0;

			if (key[KEY_SPACE]) 
				jump = 30;
			//play_sample(jumpSound, VOLUME, PAN, PITCH, FALSE);
			    
		}
		
		else {
		     	player->y -= jump/3;
		     	jump--;
		}

		if (jump < 0){
			
			if (collided(player->x + player->width/2, player->y + player->height)) {
				jump = JUMPIT;
				while (collided(player->x + player->width/2, player->y + player->height))
					player->y -= 2;
			}
		}
		
		
		///
		//collision detection
		// player collision detect with map
		if (!facing) {
		
			if (collided(player->x, player->y + player->height))
				player->x = oldpx;
		}
		
		else {
		
			if (collided(player->x + player->width, player->y + player->height))
				player->x = oldpx;
		}


		// update the map scroll position
		mapxoff = player->x + player->width/2 - WIDTH/2 + 10;
		mapyoff = player->y + player->height/2 - HEIGHT/2 + 10;

		// avoid moving beyond the map edge
		if (mapxoff < 0) 
			mapxoff = 0;
		
		if (mapxoff > (mapwidth * mapblockwidth - WIDTH))
			mapxoff = mapwidth * mapblockwidth - WIDTH;
		
		if (mapyoff < 0) 
			mapyoff = 0;
		
		if (mapyoff > (mapheight * mapblockheight - HEIGHT))
			mapyoff = mapheight * mapblockheight - HEIGHT;


		//
		//Draw things

		// draw the background tiles
		MapDrawBG(buffer, mapxoff, mapyoff, 0, 0, WIDTH - 1, HEIGHT - 1);

		// draw the foreground tiles
		MapDrawFG(buffer, mapxoff, mapyoff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);

		// draw the player's sprite
		if (facing)
			draw_sprite(buffer, player_image[player->curframe], (player->x - mapxoff), (player->y - mapyoff));
		
		else
			draw_sprite_h_flip(buffer, player_image[player->curframe], (player->x - mapxoff), (player->y - mapyoff));


		//load title
		//draw_sprite(screen, title, 160, 20);
		 //draw_sprite(buffer, title[titleSprite->curframe], (title->titleX - mapxoff), (title->y - mapyoff));
		blit(title, screen, 0, 0, 0, 0, 640, 480);


		// blit the double buffer
		vsync();
		acquire_screen();
		blit(buffer, screen, 0, 0, 0, 0, WIDTH - 1, HEIGHT - 1);
		release_screen();


		
	}// endwhile
	//	else {
	//				blit(gameOver, screen, 0, 0, 0, 0, 640, 480); 
	//}

	gameOver();


	// clean up
	for (n = 0; n < 8; n++)
		destroy_bitmap(player_image[n]);
		delete player;
		delete title;

	//	for (n=0; n<NUM_SOUNDS; n++)
	//		destroy_sample(sounds[n]);


		destroy_sample(music);
	//	destroy_sample(jumpSound);
		destroy_bitmap(title);
		destroy_bitmap(buffer);
		
		MapFreeMem();

		remove_sound();
		allegro_exit();

		return 0;

}


END_OF_MAIN()

	
void gameOver(){
	BITMAP *gameOver;
	gameOver = load_bitmap("gameover.bmp", NULL);
	blit(gameOver, screen, 0, 0, 0, 0, 640, 480); 
}
