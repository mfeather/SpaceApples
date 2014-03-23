#ifndef BULLET_H
#define BULLET_H 1
#include <allegro.h>
#include "GameSprite.h"

enum BulletType{METAL,LASER};

class Bullet : public GameSprite{
      
      protected:
           BulletType bulletType;
           
      public:
           Bullet(BulletType,int,int);
           ~Bullet();
           void setCoords(int,int);
           void update();
           bool atEdge();

};

#endif
