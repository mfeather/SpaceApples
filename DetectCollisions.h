#include <vector>
#include "Player.h"
#include "PowerUp.h"


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
void detectCollisions(Player &player,vector<Apple*>& apples,vector<PowerUp*>& powerUps,
                       vector<Bullet*>& bullets,SAMPLE *appleSnd){
     //For each apple
     for(int i=0;i<apples.size();i++){
          //If apple hits player, delete apple and call player hit
          if(isCollision(player.rectCoords(),apples[i]->rectCoords())){
               apples[i]->hitPlayer(player);
               apples.erase(apples.begin()+i);
          //If apple reaches the edge of the screen, delete apple
          }else if(apples[i]->atEdge()){
               apples.erase(apples.begin()+i);
          }
     }
     
     //For each powerUp
     for(int i=0;i<powerUps.size();i++){
          //If powerUp hits player, delete powerUp and call player hit
          if(isCollision(player.rectCoords(),powerUps[i]->rectCoords())){
               powerUps[i]->hitPlayer(player);
               powerUps.erase(powerUps.begin()+i);
          //If powerUp reaches the edge of the screen, delete powerUp
          }else if(powerUps[i]->atEdge()){
               powerUps.erase(powerUps.begin()+i);
          }
     }
     
     //For each apple
     for(int i=0;i<apples.size();i++){
          //For each bullet
          for(int bulNum = 0;bulNum < bullets.size();bulNum++){
               //If bullet hits an apple, delete both and add to score
               if(isCollision(bullets[bulNum]->rectCoords(),apples[i]->rectCoords())){
                    player.addToScore(1);
                    play_sample(appleSnd,255,128,1000,false);
                    apples.erase(apples.begin()+i);
                    bullets.erase(bullets.begin()+bulNum);
               //If bullet reaches the edge of the screen, delete
               }else if(bullets[bulNum]->atEdge()){
                    bullets.erase(bullets.begin()+bulNum);
               }
          }                                                          
     }
}
