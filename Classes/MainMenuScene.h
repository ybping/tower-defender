#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class MainMenu : public cocos2d::Sprite
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(cocos2d::CCRenderTexture* sqr);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
        
    // implement the "static create()" method manually
    
    CREATE_FUNC(MainMenu);
    
    void startGame();
    
    //通过DataModel中得gameLayer来判断游戏是否开始了
    bool isGameStarted();
    
    void gotoGameScene(Ref *pSender);
    
    void gotoContinueScene(Ref *pSender);
    
    void gotoRestartScene(Ref *pSender);
    
    void closeGame(Ref *pSender);
};

#endif // __MAINMENU_SCENE_H__
