#include <process.h>
#include "stdafx.h"
#include <mmsystem.h>
#undef SV_BM_ANY
#include "svga/svga.h"

/* The joystick global vars*/
int gAxis[2];
int gButtons[6];

#define IS_PRESSED(x) (GetAsyncKeyState(x)/*&0x8000*/)

void win32_UpdateJoystick()
{
        if (IS_PRESSED(VK_UP))
                gAxis[1] = -501;
        else 
        if (IS_PRESSED(VK_DOWN))
                gAxis[1] = 501;
        else gAxis[1]=0;

        if (IS_PRESSED(VK_LEFT))
                gAxis[0] = -501;
        else 
        if (IS_PRESSED(VK_RIGHT))
                gAxis[0] = 501;
        else
                gAxis[0]=0;
        gButtons[0]=((IS_PRESSED(0x5A))?1:0);
        gButtons[1]=((IS_PRESSED(0x58))?1:0);
        gButtons[2]=((IS_PRESSED(0x43))?1:0);
        gButtons[3]=((IS_PRESSED(VK_SPACE))?1:0);
        gButtons[4]=((IS_PRESSED(0x51))?1:0);
}
void game_thread(void *data);

void main_Start(){
  _beginthread(game_thread,0,NULL); //Game thread
}
void main_End(){
  SV_done();
}

void w32_update_screen(void *scrptr,unsigned scrpitch){
        if(!SV_update_rect_before(0,0,sv_width,sv_height))return;
        //if(!SV_update_rect_before(0,0,0,0))return;
        if(!SV_lock(0,0,sv_width,sv_height)) return;
        //assert(scrpitch<=sv_pitch);
        for(int h=0;h<sv_height;++h) memcpy((char*)locked_scr+h*sv_pitch,(char*)scrptr+h*scrpitch,sv_width*4);
        //win32_ConvertBitmap(scrptr,scrpitch,locked_scr,sv_pitch);
        SV_unlock();
}

void win32_close_window(){
}

void win32_init_window(int w,int h,HWND hw){
}

void win32InitWindow(HWND hw){
  sv_back_memory=SV_BM_SYSTEM;
  if(!SV_findmode(640,480,32,hw,1)) {
    SV_done();
  }
}

int get_current_time(){
  return timeGetTime();
}
