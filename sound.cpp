#include "sound.h"

Sound::Sound() {
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }

    loadMedia();
    
    soundEffectOff = false;
}
Sound::~Sound() {
    Mix_HaltMusic();
    Mix_HaltChannel(-1);

    Mix_FreeMusic(background_music);
    Mix_FreeChunk(getHurtEffectSound);
    background_music = NULL;
    getHurtEffectSound = NULL;

    Mix_Quit();
}

void Sound::loadMedia() {
    // load background music
    background_music = Mix_LoadMUS("sounds/background_music.mp3");
    if (background_music == NULL) {
		printf(" %s\n", Mix_GetError());
	}

    // load effect sound for base when get hurt
    getHurtEffectSound = Mix_LoadWAV("sounds/oidoioi.mp3");
    if (getHurtEffectSound == NULL) {
		printf(" %s\n", Mix_GetError());
	}
}

void Sound::playMusic() {
    Mix_PlayMusic(background_music, -1);
}

void Sound::playEffectSoundWhenGetHurt() {
    if (soundEffectOff) return;
    Mix_PlayChannel(-1, getHurtEffectSound, 0);
}

void Sound::musicInOptions() {
    if (Mix_PlayingMusic() == 1) Mix_HaltMusic();
    else playMusic();
}

void Sound::soundEffectInOptions() {
    if (!soundEffectOff) {soundEffectOff = true;}
    else soundEffectOff = false;
}