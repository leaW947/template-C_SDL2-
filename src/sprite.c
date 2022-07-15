#include "headers/sprite.h"

typedef struct Animation Animation; 

struct Animation{

    char name[255];

    float speed;
    SDL_Rect lstImage[200];
    int lstFrame[50];

    int nbFrame;

    bool bLoop;
    bool bIsFinish;

    int wFrame;
    int hFrame;

};

typedef struct Sprite Sprite;

struct Sprite{

    SDL_Texture *image;

    int x;
    int y;
    int width;
    int height;

    int scaleX;
    int scaleY;

    bool bIsTilesheet;

    float timerFrame;
    int currentFrame;

    double angle;
    SDL_RendererFlip flip;
    SDL_Point *origin;

    int num;
    int nbAnimation;

    Animation currentAnimation;
    Animation lstAnimation[200];

};

static int nbSprite=0;
static Sprite lstSprite[500];

int sprite_create(SDL_Texture *pTexture,int pX, int pY){

    Sprite mySprite;
    mySprite.image=pTexture;

    mySprite.x=pX;
    mySprite.y=pY;

    SDL_QueryTexture(pTexture,NULL,NULL,&mySprite.width,&mySprite.height);

    mySprite.scaleX=1;
    mySprite.scaleY=1;

    mySprite.bIsTilesheet=false;
    mySprite.num=nbSprite;

    mySprite.currentFrame=0;
    mySprite.timerFrame=0;

    mySprite.angle=0;
    mySprite.flip=SDL_FLIP_NONE;

    mySprite.origin=NULL;

    mySprite.nbAnimation=0;

    lstSprite[nbSprite]=mySprite;
    nbSprite+=1;

    return mySprite.num;

}

void sprite_setScale(int pNumSprite,int pScaleX, int pScaleY){

    Sprite *mySprite;
    mySprite=&lstSprite[pNumSprite];

    mySprite->scaleX=pScaleX;
    mySprite->scaleY=pScaleY;

}

void sprite_setFlip(int pNumSprite,SDL_RendererFlip pFlip){
    
    Sprite *mySprite;
    mySprite=&lstSprite[pNumSprite];

    mySprite->flip=pFlip;
}

void sprite_setRotation(int pNumSprite,double pAngle){
    
    Sprite *mySprite;
    mySprite=&lstSprite[pNumSprite];

    mySprite->angle=pAngle;
}

void sprite_addAnimation(int pNumSprite, char pName[],int pLstFrame[],int pNbFrame,int pWFrame,int pHFrame,float pSpeed,bool pbLoop){

    Sprite *mySprite;
    mySprite=&lstSprite[pNumSprite];

    mySprite->bIsTilesheet=true;

    Animation newAnimation;

    int nbCol=floor(mySprite->width/pWFrame);

    for(int n=0;n<=pNbFrame;n++){

        int nFrame=pLstFrame[n];
        newAnimation.lstFrame[n]=nFrame;

        int lin=floor(nFrame/nbCol);
        int col=floor(nFrame-(lin*nbCol));

        int x=col*pWFrame;
        int y=lin*pHFrame;

        SDL_Rect rectAnim={x,y,pWFrame,pHFrame};
        newAnimation.lstImage[n]=rectAnim;

    }

    /////////////new animation/////////////
    newAnimation.speed=pSpeed;

    newAnimation.bLoop=pbLoop;
    newAnimation.bIsFinish=false;

    newAnimation.wFrame=pWFrame;
    newAnimation.hFrame=pHFrame;

    newAnimation.nbFrame=pNbFrame;

    strcpy(newAnimation.name,pName);

    mySprite->lstAnimation[mySprite->nbAnimation]=newAnimation;
    mySprite->nbAnimation+=1;

    return;

}

void sprite_startAnimation(int pNumSprite, char pName[]){

    Sprite *mySprite;
    mySprite=&lstSprite[pNumSprite];

    ////////////no start animation
    if(strcmp(mySprite->currentAnimation.name,"")!=0){
        if(strcmp(mySprite->currentAnimation.name,pName)==0){
            return;
        }
    }

    /////////////start animation
    for(int n=0;n<mySprite->nbAnimation;n++){
        Animation *myAnimation;
        myAnimation=&mySprite->lstAnimation[n];

        if(strcmp(myAnimation->name,pName)==0){
            
            mySprite->currentAnimation=mySprite->lstAnimation[n];
            mySprite->currentFrame=0;
            mySprite->currentAnimation.bIsFinish=false;

            return;

        }
    }


}

void sprite_update(float dt){

    for(int i=0;i<nbSprite;i++){
        Sprite *mySprite;
        mySprite=&lstSprite[i];

        if(strcmp(mySprite->currentAnimation.name,"")!=0){
            mySprite->timerFrame+=dt;
     
            if(mySprite->timerFrame>=mySprite->currentAnimation.speed){
                mySprite->timerFrame=0;

                mySprite->currentFrame+=1;
            
                if(mySprite->currentFrame>mySprite->currentAnimation.nbFrame-1){
                    
                    ////loop
                    if(mySprite->currentAnimation.bLoop){
                        mySprite->currentFrame=0;
                    }else{

                        ///no loop
                        mySprite->currentFrame=mySprite->currentAnimation.nbFrame-1;
                        mySprite->currentAnimation.bIsFinish=true;
                    }

                }
            }

        }
    }

}

void sprite_draw(SDL_Renderer *pRenderer){

    for(int i=0;i<nbSprite;i++){
        Sprite *mySprite;
        mySprite=&lstSprite[i];

        if(!mySprite->bIsTilesheet){
            ///////////not tilesheet
            SDL_Rect rectImg={mySprite->x,mySprite->y,mySprite->width*mySprite->scaleX,mySprite->height*mySprite->scaleY};
            
            SDL_RenderCopyEx(pRenderer,mySprite->image,NULL,&rectImg,mySprite->angle,mySprite->origin,mySprite->flip);

        }else{
            
            ////tilesheet
            if(strcmp(mySprite->currentAnimation.name,"")!=0){

                SDL_Rect rectImg={mySprite->x,mySprite->y,mySprite->currentAnimation.wFrame*mySprite->scaleX,
                                    mySprite->currentAnimation.hFrame*mySprite->scaleY};

                SDL_RenderCopyEx(pRenderer,mySprite->image,&mySprite->currentAnimation.lstImage[mySprite->currentFrame],&rectImg,
                mySprite->angle,mySprite->origin,mySprite->flip);
            }
        }

    }

}