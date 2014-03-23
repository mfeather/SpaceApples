#ifndef MENU_H
#define MENU_H 1
#include <allegro.h>
#include <string>
#include <vector>
#include "ShmupData.h"

using namespace std;

enum Status{MMENU,OMENU,GAME,INST,CRED,PAUS,WIN,LOSE,QUIT};

class Menu{

     protected:
          BITMAP *image;
          BITMAP *bgd;
          BITMAP *cursor;
          SAMPLE *scrollSnd;
          SAMPLE *selectSnd;
          vector<string> selections;
          string title,choice;
          FONT *font1;
          FONT *titleFont;
          int x,y,width,height,cx,cy,selectNum;
          float angle;
          static int inputTimer;
          void populate();
          
     public:
          Menu(string,vector<string>,DATAFILE *);
          ~Menu();
          void draw(BITMAP *);
          void update();
          void getInput();
          bool choiceIs(string);
};

#endif
