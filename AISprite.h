#ifndef AISPRITE_H
#define AISPRITE_H 1
#include "Player.h"

class AISprite : public GameSprite{

      protected:
           int levelX;
           
      public:
           AISprite();
           ~AISprite();
           virtual void update();
           virtual void update(Rectangle);
           bool atEdge();
           virtual void hitPlayer(Player *)=0;
           virtual void hitByPlayer(Player *,int);
           int getLevelX();
};

#endif
