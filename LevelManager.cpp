#include "LevelManager.h"

LevelManager::LevelManager(){
     endOfLevel = false;
     nextLevel = "Level1";
     loadEnemies();
}

LevelManager::~LevelManager(){
     clearEnemies();
}

void LevelManager::loadEnemies(){
     currentLevel = nextLevel;
     fileName = nextLevel + ".txt";
     ifstream inFile(fileName.c_str());
     string temp,input;
     bool readFile = true;
     int x,y;
     SpriteType type;
     int enType;
     
     while(inFile>>temp && readFile){
          if(temp == "X:")
               inFile >> x;
          else if(temp == "Y:")
               inFile >> y;
          else if(temp == "TYPE:"){
               inFile >>input;
               if(input == "enemy"){
                    type = ENEMY;
                    inFile >> enType;
               }else if(input == "powerup"){
                    type = POWERUP;
                    inFile >> enType;
               }
          }else if(temp == "end_enemy"){
                if(type == ENEMY)
                     aiSprites.push_back(new Enemy((EnemyType)enType,x,y));
                else
                     aiSprites.push_back(new PowerUp((PowerType)enType,x,y));
          }else if(temp == "end_level:"){
                readFile = false;
                inFile >> endX;
          }else if(temp == "next_level:")
                inFile >> nextLevel;
     }
     inFile.close();
}

void LevelManager::clearEnemies(){
     for(int i=aiSprites.size()-1;i>0;i--)
              delete aiSprites[i];
     aiSprites.clear();
}

AISprite* LevelManager::getEnemy(int levelX){
       AISprite* aiSprite = NULL;
       
       for(int i=0;i<aiSprites.size();i++){
            if(aiSprites[i]->getLevelX() <= levelX){
                 aiSprite = aiSprites[i];
                 aiSprites.erase(aiSprites.begin() + i);
            }
       }
       
       if(levelX == endX)
            endOfLevel = true;
            
       return aiSprite;
}

string LevelManager::getName(){return currentLevel;}

void LevelManager::loadNextLevel(){
     endOfLevel = false;
     clearEnemies();
     loadEnemies();
}

bool LevelManager::isEnd(){return endOfLevel;}
