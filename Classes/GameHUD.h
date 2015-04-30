//
//  GameHUD.h
//  tower
//
//  Created by Yabin Ping on 1/27/15.
//
//

#ifndef __tower__GameHUD__
#define __tower__GameHUD__

#include "cocos2d.h"
USING_NS_CC;

class GameHUD:public Layer
{
public:
    Sprite *background;
    Sprite *curSpriteRange;
    Sprite *curSprite;
    Vector<Sprite*> avaliableTower;
    static GameHUD* mInstance;
public:
    virtual bool init();
    static GameHUD* getInstace();
    CREATE_FUNC(GameHUD);
    virtual void onEnter();
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    
    void gotoMainScene(Ref *pSender);
    
};

#endif /* defined(__tower__GameHUD__) */
