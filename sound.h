#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

class Sound {
public:
    Sound();
    ~Sound();

    void loadMedia();

    void playMusic();
    void playEffectSoundWhenGetHurt();

    void musicInOptions();
    void soundEffectInOptions();

private:
    // background music
    Mix_Music* background_music = NULL;
    // sound effect
    Mix_Chunk* getHurtEffectSound = NULL; 

    bool soundEffectOff;   
};