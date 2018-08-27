#include "stdafx.h"
#include "svga/svga.h"

#include "ball.h"
#include "racket.h"
#include "block.h"

#include <vector>

//This function update full screen from scrptr. The array should be at least sv_height*scrpitch bytes size;
void w32_update_screen(void *scrptr,unsigned scrpitch);

//If this variable sets to true - game will quit

extern bool game_quited;

// these variables provide access to joystick and joystick buttons
// In this version joystick is simulated on Arrows and Z X buttons

// [0]-X axis (-501 - left; 501 - right)
// [1]-Y axis (-501 - left; 501 - right)
extern int gAxis[2];
//0 - not pressed; 1 - pressed
extern int gButtons[6];



//sv_width and sv_height variables are width and height of screen
extern unsigned int sv_width,sv_height;

bool move_left, move_right;
Ball ball;
Racket racket;
std::vector<Block> blocks;
bool play = false;


//These functions called from another thread, when a button is pressed or released
void win32_key_down(unsigned k){
  if(k==VK_F1) game_quited=true;
  if (k == VK_LEFT) move_left = true;
  if (k == VK_RIGHT) move_right = true;
}
void win32_key_up(unsigned k)
{
	if (k == VK_LEFT) move_left = false;
	if (k == VK_RIGHT) move_right = false;
	if (k == VK_SPACE) play = true;
}

//This is default fullscreen shadow buffer. You can use it if you want to.
static unsigned *shadow_buf=NULL;


void init_game(){
  shadow_buf=new unsigned [sv_width*sv_height];
  
  racket.setscreen(sv_width, sv_height);
  ball.setscreen(sv_width, sv_height);

 
  for (int i = 0; i < 3; ++i)
  {
	  for (int j = 0; j < 2; ++j)
	  {
		  blocks.push_back(Block());
		  blocks[(i * 2) + j].setscreen(sv_width, sv_height);
		  blocks[(i * 2) + j].setx((i + 1) * 50 + 150);
		  blocks[(i * 2) + j].sety((j + 1) * 50 + 250);
	  }
  }
  

  move_left = false;
  move_right = false;
}

void close_game(){
  if(shadow_buf) delete shadow_buf;
  shadow_buf=NULL;
}

//draw the game to screen
void draw_game(){
  if(!shadow_buf)return;
  memset(shadow_buf,0,sv_width*sv_height*4);

  
  ball.collision(racket.getx(), racket.gety(), racket.getw(), racket.geth());
  for (auto it = blocks.begin(); it != blocks.end(); ++it)
  {
	  if (ball.collision(it->getx(),it->gety(),it->getw(),it->geth()))
	  {
		  blocks.erase(it);
		  break;
	  }		  
  }

  for (int i = 0; i < sv_width * sv_height; ++i)
  {
	  unsigned row = i / sv_width;
	  unsigned field = i % sv_width;

	  if (ball.draw(row, field))
		  *(shadow_buf + i) = ball.getRGB();
	  if (racket.draw(row, field))
		  *(shadow_buf + i) = racket.getRGB();
	  for (size_t j = 0; j < blocks.size(); ++j)
	  {
		  if (blocks[j].draw(row, field))
			  *(shadow_buf + i) = blocks[j].getRGB();
	  }

  }
  
  

  
  //here you should draw anything you want in to shadow buffer. (0 0) is left top corner
  w32_update_screen(shadow_buf,sv_width*4);
}

//act the game. dt - is time passed from previous act
void act_game(float dt){
	if (blocks.empty())
		game_quited = true;
	if (move_left)
		racket.move_left();
	if (move_right)
		racket.move_right();
	if (play)
		if (!ball.move(dt))
			game_quited = true;
}
