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

    void clickOnMusicItem();
    void clickOnSoundItem();

    bool playingMusic();
    bool playingSound();

private:
    // background music
    Mix_Music* background_music = NULL;
    // sound effect
    Mix_Chunk* getHurtEffectSound = NULL; 

    bool musicPlaying, soundPlaying;
};