#include <allegro.h>
#include "GameSprite.h"

GameSprite::GameSprite(){health = 1;}

GameSprite::~GameSprite(){}

void GameSprite::draw(BitmapManager *bmpMan){
     bmpMan->blitToBuff(image,direction*width,(int)frame*height,x,y,width,height);
}

SpriteType GameSprite::getType(){return type;}

Rectangle GameSprite::rectCoords(){
     Rectangle temp;
     temp.x = colRectangle.x + x;
     temp.w = colRectangle.w;
     temp.y = colRectangle.y + y;
     temp.h = colRectangle.h;
     return temp;
}

int GameSprite::getHealth(){return health;}
