#include <allegro.h>
#include "Background.h"

Background::Background(){
     x = y = 0;
     width = 640;
     height = 480;
     loopX = 0;
     levelX = 0;
     image = Bmp_Background;
}

Background::~Background(){}

void Background::draw(BitmapManager *bmpMan){
     bmpMan->blitToBuff(image,loopX,0,x,y,width,height);
}

void Background::update(){
     if(loopX >= 1280)
          loopX = 0;
     else
          loopX++;
     
     levelX++;
}

int Background::getLevelX(){return levelX;}

void Background::resetLevelX(){levelX = 0;}
