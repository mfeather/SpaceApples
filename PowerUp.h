#ifndef POWERUP_H
#define POWERUP_H 1
#include "AISprite.h"

enum PowerType {POWER,SPEED,SCORE};

class PowerUp : public AISprite{
      
      protected:
           PowerType powerType;
           
      public:
           PowerUp(PowerType,int,int);
           ~PowerUp();
           void hitPlayer(Player *);
};
#endif
