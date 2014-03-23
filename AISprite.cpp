#include "AISprite.h"

using namespace std;

AISprite::AISprite(){}

AISprite::~AISprite(){}

bool AISprite::atEdge(){
     if(x<0-width)
          return true;
     else
          return false;
}

void AISprite::update(){x-=speed;}

void AISprite::update(Rectangle rect){x-=speed;}

int AISprite::getLevelX(){return levelX;}

void AISprite::hitByPlayer(Player *player,int damage){
     health -= damage;
}
