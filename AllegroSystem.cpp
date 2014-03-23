#include "AllegroSystem.h"
#include <allegro.h>

using namespace std;

AllegroSystem::AllegroSystem(){}

AllegroSystem::~AllegroSystem(){}

void AllegroSystem::setup(){
     /* Initialization */
    allegro_init();
    install_keyboard();
    install_timer();
    install_mouse();
    install_sound( DIGI_AUTODETECT, MIDI_AUTODETECT, 0 );
    install_joystick(JOY_TYPE_AUTODETECT);
    set_color_depth( 16 );
    bool fullscreen = false;
    setFull(fullscreen);
}

void AllegroSystem::setFull(bool isFull){
     fullscreen = isFull;
     if ( fullscreen == true ) // For fullscreen
          set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);
     else // For windowed
          set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
}

void AllegroSystem::toggleFull(){
     if(fullscreen)
          setFull(false);
     else
          setFull(true);
}
