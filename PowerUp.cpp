#include "PowerUp.h"
#include "Player.h"

PowerUp::PowerUp(PowerType kind,int newX,int newY){
     type = POWERUP;
     powerType = kind;
     image = Bmp_PowerUp;
     width = 16;
     height = 16;
     frame = 0.0;
     direction = (Direction)powerType;
     speed = 1;
     levelX = newX;
     x = 640;
     y = newY;
     colRectangle.x = 3;
     colRectangle.y = 1;
     colRectangle.w = 25;
     colRectangle.h = 29;
}

PowerUp::~PowerUp(){}

void PowerUp::hitPlayer(Player *player){
     if(powerType == SPEED)
          player->addToSpeed(1);
     else if(powerType == POWER)
          player->addToShots(0.5);
     else if(powerType == SCORE)
          player->addToScore(50);
}
