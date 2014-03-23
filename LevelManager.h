#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H 1
#include <string>
#include <vector>
#include <fstream>
#include "Enemy.h"
#include "PowerUp.h"

using namespace std;

class LevelManager{
      
      protected:
           string currentLevel,nextLevel,fileName;
           vector<AISprite*> aiSprites;
           void loadEnemies();
           void clearEnemies();
           bool endOfLevel;
           int endX;
      
      public:
           LevelManager();
           ~LevelManager();
           AISprite* getEnemy(int);
           string getName();
           void loadNextLevel();
           bool isEnd();
           

};
#endif
