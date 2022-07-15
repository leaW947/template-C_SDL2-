#include "headers/main.h"

#include "utils.c"
#include "gameplayService.c"
#include "assetManager.c"
#include "sceneLoader.c"

void load(SDL_Renderer *pRenderer,int pScreenWidth,int pScreenHeight){

    ///add images and sounds

    gameplayService_setSizeScreen(pScreenWidth,pScreenHeight);
    gameplayService_setRenderer(pRenderer);

    sceneLoader_load();
    sceneLoader_init("gameplay");
    
}

void update(float dt){
    sceneLoader_update(dt);
}

void draw(){
    sceneLoader_draw();
}

void keypressed(SDL_Scancode pKey){
    sceneLoader_keypressed(pKey);

}

void mousepressed(Uint8 pBtn,int pX, int pY){
    sceneLoader_mousepressed(pBtn,pX,pY);
}

void mousemoved(int pX, int pY){
   
    sceneLoader_mousemoved(pX,pY);

}

void deleteAsset(){
    
    assetManager_deleteAssets();
    graphics_deleteTexture();

}