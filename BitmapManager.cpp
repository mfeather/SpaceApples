#include "BitmapManager.h"

BitmapManager::BitmapManager(){
     bmpData = load_datafile("ShmupBmp.dat");
     buffer = create_bitmap(640,480);
}

BitmapManager::~BitmapManager(){
     destroy_bitmap(buffer);
     unload_datafile(bmpData);
}

void BitmapManager::blitToBuff(int bmpNum,int srcX,int srcY,int destX,int destY,int w,int h){
     masked_blit((BITMAP*)bmpData[bmpNum].dat,buffer,srcX,srcY,destX,destY,w,h);
}

void BitmapManager::blitScreen(){
     blit(buffer,screen,0,0,0,0,640,480);
}
