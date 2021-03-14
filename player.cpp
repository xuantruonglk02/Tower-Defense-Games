#include "player.h"

Player::Player(SDL_Renderer* &gRenderer) {
    mTexture = loadTexture(gRenderer, PLAYER_PATH);
    playerX = PLAY_ZONE_X + PLAY_ZONE_W/2;
    playerY = PLAY_ZONE_Y + PLAY_ZONE_H/2;
}

Player::~Player() {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
}

SDL_Texture* Player::getTexture() {return mTexture;}
double Player::getX() {return playerX;}
double Player::getY() {return playerY;}

void Player::setX(double x) {
    if (x - PLAYER_SIZE/2 >= PLAY_ZONE_X && x + PLAYER_SIZE/2 <= PLAY_ZONE_X + PLAY_ZONE_W)
        playerX = x;
}

void Player::setY(double y) {
    if (y - PLAYER_SIZE/2 >= PLAY_ZONE_Y && y + PLAYER_SIZE/2 <= PLAY_ZONE_Y + PLAY_ZONE_H)
        playerY = y;
}

void Player::drawPlayer(SDL_Renderer* &gRenderer) {
    SDL_Rect dstrect;
    dstrect.x = playerX - PLAYER_SIZE/2;
    dstrect.y = playerY - PLAYER_SIZE/2;
    dstrect.h = PLAYER_SIZE; dstrect.w = PLAYER_SIZE;
    SDL_RenderCopy(gRenderer, mTexture, NULL, &dstrect);
}
