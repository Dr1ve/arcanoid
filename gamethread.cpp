#include "stdlib.h"

bool game_quited=false;

int get_current_time();

void init_game();
void close_game();
void draw_game();
void act_game(float time);

void win32_UpdateJoystick();

void game_thread(void *data){
  //TODO: game init code
  init_game();
  int ticks1=get_current_time();
  while(!game_quited){
    //TODO: game infinite loop code
    draw_game();
    
    win32_UpdateJoystick();
    
    int ticks2=get_current_time();

    act_game((ticks2-ticks1)/1000.0f);
    ticks1=ticks2;
    //TODO: game main code
  };
  //TODO: game quit code
  close_game();
  exit(0);
}
