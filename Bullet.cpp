#include <allegro.h>
#include <cstdlib>
#include <ctime>
#include "Bullet.h"

using namespace std;

Bullet::Bullet(BulletType kind,int playerX,int playerY){
     type = BULLET;
     bulletType = kind;
     image = Bmp_Bullet;
     width = 16;
     height = 8;
     frame = 0.0;
     direction = (Direction)bulletType;
     speed = 5;
     if(bulletType == LASER)
          speed*=-1;
     setCoords(playerX,playerY);
     colRectangle.x = 0;
     colRectangle.y = 0;
     colRectangle.w = width;
     colRectangle.h = height;
}

Bullet::~Bullet(){}

void Bullet::setCoords(int newX,int newY){
     x = newX;
     y = newY;
}

bool Bullet::atEdge(){
     if(x>640||x<0)
          return true;
     else
          return false;
}

void Bullet::update(){
     x+=speed;
}

