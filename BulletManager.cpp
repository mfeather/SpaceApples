#include "BulletManager.h"

BulletManager::BulletManager(){}

BulletManager::~BulletManager(){
     
     for(int i=0;i<bullets.size();i++)
          delete bullets[i];
     bullets.clear();
}

void BulletManager::update(){
     for(int i=0;i<bullets.size();i++)
          bullets[i]->update();
}

void BulletManager::draw(BitmapManager* bmpMan){
     for(int i=0;i<bullets.size();i++)
          bullets[i]->draw(bmpMan);
}

void BulletManager::addBullet(Bullet* bullet){bullets.push_back(bullet);}

void BulletManager::eraseBullet(int num){
     delete bullets[num];
     bullets.erase(bullets.begin()+num);
}

Bullet* BulletManager::getBullet(int num){return bullets[num];}

int BulletManager::numBullets(){return bullets.size();}
