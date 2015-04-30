//
//  LoadScene.h
//  tower
//
//  Created by Yabin Ping on 3/6/15.
//
//

#ifndef __tower__LoadScene__
#define __tower__LoadScene__
USING_NS_CC;

class LoadingScene :public cocos2d::Layer{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    
    CREATE_FUNC(LoadingScene);
    
    virtual void onEnter();
    
    bool onTouchBegan(Touch *touch, Event *event);
    
};
#endif /* defined(__tower__LoadScene__) */
