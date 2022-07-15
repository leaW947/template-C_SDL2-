#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int sprite_create(SDL_Texture *pTexture,int pX, int pY);

void sprite_setScale(int pNumSprite,int pScaleX, int pScaleY);

void sprite_setFlip(int pNumSprite,SDL_RendererFlip pFlip);

void sprite_setRotation(int pNumSprite,double pAngle);

void sprite_addAnimation(int pNumSprite, char pName[],int pLstFrame[],int pNbFrame,int pWFrame,int pHFrame,float pSpeed,bool pbLoop);

void sprite_startAnimation(int pNumSprite, char pName[]);

void sprite_update(float dt);

void sprite_draw(SDL_Renderer *pRenderer);
