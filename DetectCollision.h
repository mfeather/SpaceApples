#include <vector>
#include "Player.h"
#include "PowerUp.h"
#include "ShmupSnd.h"


bool isCollision( Rectangle A, Rectangle B )
{
     if ( A.x < B.x + B.w &&
     A.x + A.w > B.x &&
     A.y < B.y + B.h &&
     A.y + A.h > B.y )
     {
          return true;
     }
     return false;
}

//Collision detection function
void detectCollisions(Player *player,vector<AISprite*>& aiSprites,
                       BulletManager &bullMan,SoundManager *sndMan){
     
     //For each enemy
     for(int i=0;i<aiSprites.size();i++){
          //If an enemy hits the edge, erase it
          if(aiSprites[i]->atEdge()){
               delete aiSprites[i];
               aiSprites.erase(aiSprites.begin()+i);
          }
     }
     //For each bullet
     for(int j=0;j<bullMan.numBullets();j++){
          //If a bullet hits the edge, erase it
          if(bullMan.getBullet(j)->atEdge())
               bullMan.eraseBullet(j);
     }
     //For each enemy
     for(int i=0;i<aiSprites.size();i++){
          //If the player hits the enemy
          if(isCollision(player->rectCoords(),aiSprites[i]->rectCoords())){
                 //If the enemy is a pickup, play the sound
                 if(aiSprites[i]->getType() == POWERUP)
                      sndMan->playSample(Snd_PowerUp);
                 //Call hitPlayer and erase the enemy
                 aiSprites[i]->hitPlayer(player);
                 aiSprites[i]->hitByPlayer(player,1);
                 if(aiSprites[i]->getType() == ENEMY && !player->isInvincible())
                      sndMan->playSample(Snd_EnemyDeath);
                 if(aiSprites[i]->getHealth() <= 0){
                      delete aiSprites[i];
                      aiSprites.erase(aiSprites.begin()+i);
                 }   
          }
     }
     //For each enemy
     for(int i=0;i<aiSprites.size();i++){
          //For each bullet
          for(int j=0;j<bullMan.numBullets();j++){
               //If the bullet hits the enemy
               if(isCollision(aiSprites[i]->rectCoords(),bullMan.getBullet(j)->rectCoords())){
                    if(aiSprites[i]->getType() == ENEMY){
                         //Add to score and erase both
                         bullMan.eraseBullet(j);
                         aiSprites[i]->hitByPlayer(player,1);
                         sndMan->playSample(Snd_EnemyDeath);
                         if(aiSprites[i]->getHealth() <= 0){
                              player->addToScore(1);
                              delete aiSprites[i];
                              aiSprites.erase(aiSprites.begin()+i);
                         }
                    }
               }
          } 
     }
}
