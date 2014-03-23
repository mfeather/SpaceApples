#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H 1
#include <vector>
#include "Bullet.h"

using namespace std;

class BulletManager{

      protected:
           vector<Bullet*> bullets;
           
      public:
           BulletManager();
           ~BulletManager();
           void update();
           void draw(BitmapManager*);
           void addBullet(Bullet*);
           void eraseBullet(int);
           Bullet* getBullet(int);
           int numBullets();      

};
#endif
