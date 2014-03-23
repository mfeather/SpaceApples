#include <allegro.h>
#include "Player.h"
#include "ShmupSnd.h"

Player::Player(SoundManager *sm){
     type = PLAYER;
     sndMan = sm;
     image = Bmp_Player;
     width = 128;
     height = 128;
     frame = 0.0;
     direction = CENTER;
     speed = 2;
     shotsPerSec = 2.0;
     lives = 3;
     health = 3;
     x = 20;
     y = 240;
     score = 0;
     colRectangle.x = 22;
     colRectangle.y = 30;
     colRectangle.w = 100;
     colRectangle.h = 70;
}

Player::~Player(){
     sndMan = NULL;
}

void Player::getInput(BulletManager &bullMan){
     poll_joystick();
     if(key[KEY_UP]||joy[0].stick[0].axis[1].d1){
          move(UP);
          direction = UP;
     }else if(key[KEY_DOWN]||joy[0].stick[0].axis[1].d2){
          move(DOWN);
          direction = DOWN;
     }else
          direction = CENTER;
     if(key[KEY_LEFT]||joy[0].stick[0].axis[0].d1)
          move(LEFT);
     else if(key[KEY_RIGHT]||joy[0].stick[0].axis[0].d2)
          move(RIGHT);
     if((key[KEY_SPACE]||joy[0].button[0].b) && cooldown<=0 && !isInvincible()){
          bullMan.addBullet(new Bullet(METAL,x+width,y+height/2));
          sndMan->playSample(Snd_PlayerShot);
          cooldown = (int)(90/shotsPerSec);
     }else
          cooldown--;
}

void Player::update(){
     frame += 0.2;
     if(frame >= 2.0)
          frame = 0.0;
     if(invincible>0)
          invincible--;
}

void Player::move(Direction dir){
     if(dir == UP && y>-30)
          y-=speed;
     if(dir == DOWN && y<500-height)
          y+=speed;
     if(dir == LEFT && x>-10)
          x-=speed;
     if(dir == RIGHT && x<640-width)
          x+=speed;
}

void Player::addToScore(int points){
     score += points;
}

void Player::addToSpeed(int amount){
     if(speed + amount <= 5)
          speed += amount;
}

void Player::addToShots(double amount){
     if(shotsPerSec + amount <= 5)
          shotsPerSec += amount;
}

void Player::hit(int damage){
     if(!isInvincible()){
          health -= damage;
          if(health <= 0){
               invincible = 180;
               x = 20;
               y = 240;
               lives--;
               health = 3;
               sndMan->playSample(Snd_PlayerDeath);
          }else
               sndMan->playSample(Snd_PlayerHit);
     }
}

int Player::getScore(){return score;}

int Player::getLives(){return lives;}

bool Player::atEdge(){return false;}

bool Player::isInvincible(){
     if(invincible > 0)
          return true;
     else
          return false;
}

int Player::cooldown = 0;
int Player::invincible = 0;
