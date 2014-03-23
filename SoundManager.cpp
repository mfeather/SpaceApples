#include "SoundManager.h"

SoundManager::SoundManager(){
     sndData = load_datafile("ShmupSnd.dat");
}

SoundManager::~SoundManager(){
     unload_datafile(sndData);
}

void SoundManager::playSample(int sndNum){
     play_sample((SAMPLE*)sndData[sndNum].dat,100,128,1000,false);
}

void SoundManager::loopSample(int sndNum){
     play_sample((SAMPLE*)sndData[sndNum].dat,255,128,1000,true);
}

void SoundManager::stopSample(int sndNum){
     stop_sample((SAMPLE*)sndData[sndNum].dat);
}
