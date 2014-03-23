#ifndef BOSS1GUN_H
#define BOSS1GUN_H 1
#include <cmath>
#include "AISprite.h"
#include "ShmupBmp.h"

class Boss1Gun : public AISprite{
     protected:
          float angle;
          int xOffset,yOffset;
          BITMAP *img;
     public:
          Boss1Gun(Rectangle,int,int);
          ~Boss1Gun();
          void update(Rectangle);
          void update(Rectangle,Rectangle);
          void hitPlayer(Player *player);
          void draw(BitmapManager *);
};
#endif
