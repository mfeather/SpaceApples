#ifndef GAMESPRITE_H
#define GAMESPRITE_H 1
#include <allegro.h>
#include "BitmapManager.h"
#include "ShmupBmp.h"
#include "Rectangle.h"

enum Direction{UP=0,CENTER=1,DOWN=2,LEFT=3,RIGHT=4};
enum SpriteType{PLAYER,ENEMY,POWERUP,BULLET};

const double PI = 3.14159265;

class GameSprite{
      
      protected:
           Rectangle colRectangle;
           SpriteType type;
           int x,y,width,height,speed,health;
           Direction direction;
           double frame;
           int image;
           
      public:
           GameSprite();
           ~GameSprite();
           SpriteType getType();
           virtual void update()=0;
           virtual bool atEdge()=0;  
           virtual void draw(BitmapManager *);
           Rectangle rectCoords();
           int getHealth();

};
#endif
