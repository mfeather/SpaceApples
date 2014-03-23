#include "Boss1Gun.h"

Boss1Gun::Boss1Gun(Rectangle bossCoords,int xOff,int yOff){
     xOffset = xOff;
     yOffset = yOff;
     x = bossCoords.x + xOffset;
     y = bossCoords.y + yOffset;
     angle = 0.0;
     image = Bmp_Boss1Gun;
     img = load_bitmap("Boss1Gun.bmp",NULL);
}

Boss1Gun::~Boss1Gun(){
     destroy_bitmap(img);
}

void Boss1Gun::update(Rectangle playerCoords,Rectangle boss1Coords){
     x = boss1Coords.x + xOffset;
     y = boss1Coords.y + yOffset;
     angle = atan2(playerCoords.y + playerCoords.h/2.0 - y,
                   playerCoords.x + playerCoords.w/2.0 - x)
                   * 255.0/(2.0 * PI);
}

void Boss1Gun::update(Rectangle rect){}

void Boss1Gun::draw(BitmapManager *bmpMan){
     pivot_scaled_sprite(bmpMan->buffer,img,x,y,14,24,ftofix(angle),ftofix(1.5));
}

void Boss1Gun::hitPlayer(Player *player){
     player->hit(player->getHealth());
}
