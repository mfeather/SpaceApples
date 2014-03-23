#ifndef BACKGROUND_H
#define BACKGROUND_H 1
#include <allegro.h>
#include "BitmapManager.h"
#include "ShmupBmp.h"

class Background{
      
      protected:
           int x,y,width,height,loopX,levelX;
           int image;
           
      public:
           Background();
           ~Background();
           void draw(BitmapManager *);
           void update();
           int getLevelX();
           void resetLevelX();
};

#endif
