#ifndef ENEMY_H
#define ENEMY_H 1
#include <allegro.h>
#include "AISprite.h"
#include "Player.h"

enum EnemyType{APPLE,ORANGE,GRAPE,MELON,BOSS};

class Enemy : public AISprite{
      
      protected:
           EnemyType enemyType;
           int initY;
           
      public:
           Enemy();
           Enemy(EnemyType,int,int);
           ~Enemy();
           void setRandom();
           virtual void update(Rectangle);
           virtual void hitPlayer(Player *);
           void hitByPlayer(Player *,int);

};

#endif
