#ifndef BOSS_H
#define BOSS_H 1
#include <vector>
#include "Enemy.h"
#include "Boss1Gun.h"

class Boss : public Enemy{
      
      protected:
           Rectangle moveRect;
           int vertSpeed;
           vector<Boss1Gun*> guns;
      public:
           Boss();
           ~Boss();
           void update(Rectangle);
           void hitPlayer(Player *);
           void draw(BitmapManager *);

};
#endif
