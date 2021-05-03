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
    void playClickSound();
    void playEffectSoundWhenGetHurt();
    void playGunShottingSound();
    void playLazeShottingSound();
    void playBoomSound();

    void clickOnMusicItem();
    void clickOnSoundItem();

    bool playingMusic();
    bool playingSound();

private:
    // background music
    Mix_Music* background_music = NULL;
    // sound effect
    // get hit
    Mix_Chunk* getHurtEffectSound = NULL;
    // gun shot
    Mix_Chunk* gunShottingSound = NULL;
    // laze shot
    Mix_Chunk* lazeShottingSound = NULL;
    // boom
    Mix_Chunk* boomSound = NULL;
    // click
    Mix_Chunk* clickSound = NULL;

    bool musicPlaying, soundPlaying;
};