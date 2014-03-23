#ifndef PLAYER_H
#define PLAYER_H 1
#include <allegro.h>
#include <vector>
#include "BulletManager.h"
#include "SoundManager.h"
#include "ShmupData.h"

using namespace std;

class Player : public GameSprite{
      
      protected:
           int score,lives;
           double shotsPerSec;
           static int cooldown;
           static int invincible;
           SoundManager* sndMan;
          
      public:
           Player(SoundManager*);
           ~Player();
           void getInput(BulletManager&);
           void update();
           void move(Direction);
           void addToScore(int);
           void addToSpeed(int);
           void addToShots(double);
           void hit(int);
           int getScore();
           int getLives();
           bool atEdge();
           bool isInvincible();
     
};
#endif
