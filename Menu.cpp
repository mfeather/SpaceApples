#include "Menu.h"
#include <cmath>

Menu::Menu(string name,vector<string> selects,DATAFILE *datafile){
     
     selections = selects;
     title = name;
     choice = "NONE";
     bgd = (BITMAP *)datafile[Data_Background].dat;
     cursor = (BITMAP *)datafile[Data_Apple].dat;
     scrollSnd = (SAMPLE *)datafile[Data_MenuScrollSnd].dat;
     selectSnd = (SAMPLE *)datafile[Data_MenuSelectSnd].dat;
     x = 0;
     y = 0;
     cx = 216;
     cy = 216;
     angle = 0.0;
     width = 640;
     height = 480;
     selectNum = 0;
     font1 = (FONT *)datafile[Data_PCText].dat;
     titleFont = (FONT *)datafile[Data_ClassicText].dat;
     image = create_bitmap(width,height);
     populate();
}

Menu::~Menu(){
     selections.clear();
}

void Menu::draw(BITMAP *dest){
     masked_blit(image,dest,0,0,x,y,width,height);
}

void Menu::getInput(){
     poll_joystick();
     if(inputTimer <= 0){
          if(key[KEY_UP]||joy[0].stick[0].axis[1].d1){
               selectNum--;
               if(selectNum < 0)
                    selectNum = selections.size()-1;
               play_sample(scrollSnd,100,128,1000,false);
               inputTimer = 40;
          }else if(key[KEY_DOWN]||joy[0].stick[0].axis[1].d2){
               selectNum++;
               if(selectNum >= selections.size())
                    selectNum = 0;
               play_sample(scrollSnd,100,128,1000,false);
               inputTimer = 40;
          }else if(key[KEY_ENTER]||joy[0].button[0].b){
               play_sample(selectSnd,100,128,1000,false);
               choice = selections[selectNum];
               inputTimer = 40;
          }
     }
     inputTimer--;
}

bool Menu::choiceIs(string input){
       if(choice == input){
            choice = "NONE";
            return true;
       }else
            return false;
}

void Menu::update(){
     poll_mouse();
     angle = atan2(mouse_y-cy,mouse_x-cx)*255.0/(2.0*3.14150926);
     masked_blit(bgd,image,0,0,x,y,width,height);
     populate();
     cy = 190 + 50*selectNum;
     //masked_blit(cursor,image,0,0,cx,cy,32,32);
     pivot_sprite(image,cursor,cx,cy,16,16,ftofix(angle));
     //angle++;
}

void Menu::populate(){
     textprintf_centre_ex(image,titleFont,width/2,100,makecol(200,200,255),-1,"%s",title.c_str());
     for(int i=0;i<selections.size();i++)
             textprintf_ex(image,font1,250,200+i*50,makecol(0,200,0),-1,"%s",selections[i].c_str());
}

int Menu::inputTimer = 0;
