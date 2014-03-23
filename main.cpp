//Created by Mark Feather

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>
#include <allegro.h>
#include "AllegroSystem.h"
#include "Background.h"
#include "Player.h"
#include "Boss.h"
#include "PowerUp.h"
#include "DetectCollision.h"
#include "Menu.h"
#include "LevelManager.h"
#include "SoundManager.h"
#include "BitmapManager.h"
#include "BulletManager.h"
#include "ShmupData.h"
#include "ShmupSnd.h"

using namespace std;

//variable and function for FPS timer
volatile long counter = 0;
void incCtr(){counter++;}

int main()
{
    //Seed random function
    srand(time(NULL));
    
    //Initiate Allegro
    AllegroSystem sys;
    sys.setup();
    
    //Lock data and start timer for FPS
    LOCK_VARIABLE(counter);
    LOCK_FUNCTION(incCtr);
    install_int_ex(incCtr,BPS_TO_TIMER(90));
    
    //Create objects
    DATAFILE *datafile = load_datafile("Shmup.dat");
    BITMAP *buffer = create_bitmap(640,480);
    FONT* pcFont;
    FONT* silkFont;
    FONT* classicFont;
    pcFont = (FONT *)datafile[Data_PCText].dat;
    silkFont = (FONT *)datafile[Data_SilkText].dat;
    classicFont = (FONT *)datafile[Data_ClassicText].dat;
    vector<AISprite*> aiSprites;
    SoundManager *sndManager = new SoundManager();
    BitmapManager *bmpManager = new BitmapManager();
    
    //Set game status to Main Menu
    //Enum defined in Menu.h
    Status status = MMENU;
    //Create Main Menu               
     string mainSelects[] = {"Play Game","Options","Credits","Quit"};
     vector<string> menuSelects(mainSelects,mainSelects + sizeof(mainSelects) / sizeof(string));
     Menu mainMenu("Space Apples",menuSelects,datafile);
    
     //Create Pause Menu               
     string pausSelects[] = {"Resume Game","Main Menu"};
     vector<string> pauseSelects(pausSelects,pausSelects + sizeof(pausSelects) / sizeof(string));
     Menu pauseMenu("Paused",pauseSelects,datafile);
     
     //Create Options Menu               
     string optSelects[] = {"Toggle Fullscreen","Back"};
     vector<string> optionSelects(optSelects,optSelects + sizeof(optSelects) / sizeof(string));
     Menu optionsMenu("Options",optionSelects,datafile);
    
    //Program loop
    while(status!=QUIT){
         
         
         
         //Main menu loop
         while(status == MMENU){
                         
               //Inside FPS loop
               while(counter > 0){
                    //Update menu
                    mainMenu.update();
                    mainMenu.getInput();
                    counter--;
               } //End of FPS Loop
          
               //check for game status
               if(mainMenu.choiceIs("Play Game")){
                    status = GAME;
                    //Start background music
                    sndManager->loopSample(Snd_BGM);
               }else if(mainMenu.choiceIs("Options"))
                    status = OMENU;
               else if(mainMenu.choiceIs("Credits"))
                    status = CRED;
               else if(mainMenu.choiceIs("Quit"))
                    status = QUIT;
               //Draw menu
               mainMenu.draw(buffer);
               blit( buffer, screen, 0, 0, 0, 0, 640, 480 );
               clear_bitmap( buffer );
          
         }//End of main menu loop
         
         //Options menu loop
         while(status == OMENU){
                         
               //Inside FPS loop
               while(counter > 0){
                    //Update menu
                    optionsMenu.update();
                    optionsMenu.getInput();
                    //check for game status
                    if(optionsMenu.choiceIs("Toggle Fullscreen"))
                         sys.toggleFull();
                    else if(optionsMenu.choiceIs("Back"))
                         status = MMENU;
                    counter--;
               } //End of FPS Loop
          
               //Draw menu
               optionsMenu.draw(buffer);
               blit( buffer, screen, 0, 0, 0, 0, 640, 480 );
               clear_bitmap( buffer );
          
         }//End of Options menu loop
         
         //Create Credits timer and image
         int credTimer = 1500;
         BITMAP *credits = (BITMAP *)datafile[Data_Credits].dat;
         
         //Credits loop
         while(status == CRED){
         
               credTimer--;
               if(credTimer<=0)
                    status = MMENU;
               //Draw credits
               blit(credits, screen, 0, 0, 0, 0, 640, 480 );
               clear_bitmap( buffer );
          
         }//End of Credits loop
         
         //Initialize game objects
         ifstream inFile("highScore.txt");
         LevelManager levelManager;
         Background bgd;
         Player *player = new Player(sndManager);
         BulletManager bulletManager;
         AISprite* aiSprite;
         Boss* boss;
         bool bossTime = false;
         int titleTimer = 1000;
         string levelName = levelManager.getName();
         int highScore = 0;
         int inputTimer = 0;
         inFile >> highScore;
    
         //Main game loop
         while(status == GAME){
                         
               //Inside FPS loop
               while(counter > 0){
                    
                    //Get the next enemy
                    aiSprite = levelManager.getEnemy(bgd.getLevelX());
                    if(aiSprite != NULL){
                         aiSprites.push_back(aiSprite);
                    }
               
                    //Detect collisions of objects
                    detectCollisions(player,aiSprites,bulletManager,sndManager);
               
                    //If it is the end of the level, load the next level
                    if(levelManager.isEnd()&&!bossTime){
                         boss = new Boss();
                         aiSprites.push_back(boss);
                         bossTime = true;
                    }
                    
                    if(bossTime && boss->getHealth() <= 0){
                         bossTime = false;
                         titleTimer = 1000;
                         levelManager.loadNextLevel();
                         bgd.resetLevelX();
                         levelName = levelManager.getName();
                    }
                    
                    //Update sprites
                    bgd.update();
                    player->update();
                    bulletManager.update();
                    for(int i=0;i<aiSprites.size();i++)
                         aiSprites[i]->update(player->rectCoords());
                    player->getInput(bulletManager);
               
                    //Update the High Score
                    if(player->getScore()>highScore)
                         highScore = player->getScore();
                    
                    //Check Pause button
                    poll_joystick();
                    if((key[KEY_ESC]||joy[0].button[3].b) && inputTimer <=0){
                         status = PAUS;
                         inputTimer = 50;
                    }
                    if(inputTimer >0)
                         inputTimer--;
                    if(player->getLives() <= 0)
                         status = MMENU;
                    
                    counter--;
               } //End of FPS Loop
          
               //Draw sprites
               bgd.draw(bmpManager);
               player->draw(bmpManager);
               bulletManager.draw(bmpManager);
               for(int i=0;i<aiSprites.size();i++)
                    aiSprites[i]->draw(bmpManager);
                    
               //Draw health bar
               for(int i=0;i<player->getHealth();i++)
                    rectfill(bmpManager->buffer,150 + i*50,455,195+i*50,475,makecol(255,0,0));
                    
               if(bossTime){
                    for(int i=0;i<boss->getHealth();i++)
                         rectfill(bmpManager->buffer,200 + i*10,15,208+i*10,22,makecol(200,100,200));
               }
               //Print scores and lives
               poll_mouse();
               textprintf_ex(bmpManager->buffer,silkFont,10,455,makecol(0,255,0),-1,"HEALTH: ");
               textprintf_ex(bmpManager->buffer,silkFont,10,10,makecol(0,255,0),-1,"SCORE: %i",player->getScore());
               textprintf_right_ex(bmpManager->buffer,silkFont,630,10,makecol(0,255,0),-1,"HIGH SCORE: %i",highScore);
               textprintf_right_ex(bmpManager->buffer,silkFont,630,455,makecol(0,255,0),-1,"LIVES: %i",player->getLives());
               //Print title of level
               if(titleTimer >0){
                    titleTimer--;
                    textprintf_ex(bmpManager->buffer,classicFont,220,220,makecol(0,0,200),-1," %s",levelName.c_str());
               }
               bmpManager->blitScreen();
               clear_bitmap(bmpManager->buffer);
               
               //Pause menu loop
               while(status == PAUS){
                         
                    //Inside FPS loop
                    while(counter > 0){
                         //Update menu
                         pauseMenu.update();
                         pauseMenu.getInput();
                         //check for game status
                         if(pauseMenu.choiceIs("Resume Game"))
                              status = GAME;
                         else if(pauseMenu.choiceIs("Main Menu"))
                              status = MMENU;
                         counter--;
                    } //End of FPS Loop
          
                    //Draw menu
                    pauseMenu.draw(buffer);
                    blit( buffer, screen, 0, 0, 0, 0, 640, 480 );
                    clear_bitmap( buffer );
          
              }//End of Pause menu loop
               
         }//End of main game loop
    
         //Save the high score
         ofstream outFile("highScore.txt");
         outFile << highScore;
         
         //Clear sprites
         for(int i=0;i<aiSprites.size();i++)
              delete aiSprites[i];
         aiSprites.clear();
         delete player;
         sndManager->stopSample(Snd_BGM);
    } //End of Program loop
       
    /* Free memory afterwards! */
    destroy_bitmap(buffer);
    delete sndManager;
    delete bmpManager;
    unload_datafile(datafile);
    return 0;
}
END_OF_MAIN();
