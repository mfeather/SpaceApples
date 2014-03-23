#ifndef ALLEGROSYSTEM_H
#define ALLEGROSYSTEM_H 1

using namespace std;

class AllegroSystem{
      
public:
       AllegroSystem();
       ~AllegroSystem();
       void setup();
       void setFull(bool);
       void toggleFull();
       
protected:
       int screenWidth, screenHeight;
       bool fullscreen;
          
};

#endif
