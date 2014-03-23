#ifndef BITMAPMANAGER_H
#define BITMAPMANAGER_H 1
#include <allegro.h>

class BitmapManager{
     protected:
          DATAFILE *bmpData;
          
     public:
          BitmapManager();
          ~BitmapManager();
          void blitToBuff(int,int,int,int,int,int,int);
          void blitScreen();
          BITMAP *buffer;

};
#endif
