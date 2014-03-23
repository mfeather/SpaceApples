#include <allegro.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Enemy.h"

using namespace std;

Enemy::Enemy(){
     type = ENEMY;
     image = Bmp_Enemies;
     width = 32;
     height = 32;
     frame = 0.0;
     direction = UP;
     speed = 1;
     setRandom();
     colRectangle.x = 3;
     colRectangle.y = 1;
     colRectangle.w = 25;
     colRectangle.h = 29;
}

Enemy::Enemy(EnemyType enType,int newX,int newY){
     type = ENEMY;
     enemyType = enType;
     image = Bmp_Enemies;
     width = 32;
     height = 32;
     frame = 0.0;
     direction = (Direction)enemyType;
     speed = 2;
     if(enemyType == APPLE)
          speed = 3;
     levelX = newX;
     x = 640;
     y = newY;
     initY = y;
     colRectangle.x = 3;
     colRectangle.y = 1;
     colRectangle.w = 25;
     colRectangle.h = 29;
}

Enemy::~Enemy(){}

void Enemy::setRandom(){
     x = 640;
     y = (int)rand()% 433 + 10;
     initY = y;
}

void Enemy::update(Rectangle playerCoords){
     x-=speed;
     if(enemyType == GRAPE)
          y = initY + (int)(50*sin(x*PI/180));
     else if(enemyType == MELON)
          y = initY + (int)(100*sin(x*PI/180));
     else if(enemyType == ORANGE){
          if(y > playerCoords.y+20)
               y--;
          else if(y < playerCoords.y+20)
               y++;
     }
}

void Enemy::hitPlayer(Player *player){
     player->hit(1);
}


void Enemy::hitByPlayer(Player *player,int damage){
     if(!player->isInvincible())
          health -= damage;
}
