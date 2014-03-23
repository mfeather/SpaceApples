#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H 1
#include <vector>
#include <allegro.h>

class SoundManager{
      protected:
           DATAFILE *sndData;
                
      public:
           SoundManager();
           ~SoundManager();
           void playSample(int);
           void loopSample(int);
           void stopSample(int);
};
#endif
