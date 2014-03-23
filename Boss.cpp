#include "Boss.h"

Boss::Boss(){
     type = ENEMY;
     enemyType = BOSS;
     image = Bmp_Boss1;
     width = 160;
     height = 256;
     frame = 0.0;
     direction = UP;
     speed = 1;
     vertSpeed = 2;
     health = 10;
     levelX = 3000;
     x = 400;
     y = 112;
     initY = y;
     colRectangle.x = 14;
     colRectangle.y = 14;
     colRectangle.w = 146;
     colRectangle.h = 228;
     moveRect.x = 300;
     moveRect.y = 50;
     moveRect.w = 340;
     moveRect.h = 380;
     guns.push_back(new Boss1Gun(rectCoords(),60,40));
     guns.push_back(new Boss1Gun(rectCoords(),60,180));            
}

Boss::~Boss(){}

void Boss::update(Rectangle playerCoords){
     x -= speed;
     y -= vertSpeed;
     if(rectCoords().x < moveRect.x
        ||rectCoords().x + rectCoords().w > moveRect.x + moveRect.w)
          speed *= -1;
     if(rectCoords().y < moveRect.y
        ||rectCoords().y + rectCoords().h > moveRect.y + moveRect.h)
          vertSpeed *= -1;
     for(int i=0;i<guns.size();i++)
          guns[i]->update(playerCoords,rectCoords());
}

void Boss::hitPlayer(Player *player){
     player->hit(player->getHealth());
}

void Boss::draw(BitmapManager *bmpMan){
     bmpMan->blitToBuff(image,direction*width,(int)frame*height,x,y,width,height);
     for(int i=0;i<guns.size();i++)
          guns[i]->draw(bmpMan);
}
