//
//  GameHUD.cpp
//  tower
//
//  Created by Yabin Ping on 1/27/15.
//
//

#include "GameHUD.h"
#include "DataModel.h"
#include <vector>
#include "MainMenuScene.h"
using namespace std;

GameHUD* GameHUD::mInstance = NULL;

bool GameHUD::init()
{
    if(!Layer::init())
        return false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    background = Sprite::create("scene/hud.png");
    background->setScaleX(2);
    background->setAnchorPoint(Point(0,0));
    this->addChild(background);
    
    //添加tower图标
    vector<string> towerFrame = {"Arrow01.png", "Star01.png", "Sun01.png", "Rocket01.png"};
    for (int i = 0; i < towerFrame.size(); ++i) {
        auto sprite = Sprite::createWithSpriteFrameName(towerFrame[i]);

        float offsetFraction = ((float)(i+1)) / (towerFrame.size()+1);
        sprite->setScale(0.6);
        sprite->setPosition(Point(visibleSize.width*offsetFraction,35));
        sprite->setContentSize(Size(50, 50));
        sprite->setName(towerFrame[i]);
        this->addChild(sprite);
        avaliableTower.pushBack(sprite);
    }
    
    auto pauseItem = MenuItemImage::create("menu/pauseA.png", "menu/pauseB.png",
                                           CC_CALLBACK_1(GameHUD::gotoMainScene, this));
    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Point(visibleSize.width - pauseItem->getContentSize().width / 2,
                            visibleSize.height - pauseItem->getContentSize().height / 2));
    this->addChild(menu);
    return true;
}

void GameHUD::gotoMainScene(Ref *pSender)
{
    CCLOG("GameHUD gotomainScene");
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Select.mp3");
    //得到窗口的大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    RenderTexture *renderTexture = RenderTexture::create(visibleSize.width,visibleSize.height);
    
    //遍历当前类的所有子节点信息，画入renderTexture中。
    //这里类似截图。
    renderTexture->begin();
    this->getParent()->visit();
    renderTexture->end();
    
    //将游戏界面暂停，压入场景堆栈。并切换到GamePause界面
    auto scene = MainMenu::createScene(renderTexture);
    Director::getInstance()->pushScene(scene);
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BGMusic.mp3",true);

}
GameHUD* GameHUD::getInstace()
{
    if(mInstance ==  nullptr)
        mInstance = GameHUD::create();
    return mInstance;
}

void GameHUD::onEnter()
{
    Layer::onEnter();
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameHUD::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameHUD::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameHUD::onTouchEnded, this);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}

bool GameHUD::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));
    Sprite *newSprite = NULL;
    
    for(auto sprite : this->avaliableTower)
    {
        Rect posRect = Rect((sprite->getPositionX() - sprite->getContentSize().width / 2),
                             (sprite->getPositionY() - sprite->getContentSize().height / 2),
                             sprite->getContentSize().width, sprite->getContentSize().height);
        if(posRect.containsPoint(touchLocation))
        {
            //添加攻击范围圈圈
            this->curSpriteRange = Sprite::create("Range.png");
            this->curSpriteRange->setScale(3);
            this->addChild(this->curSpriteRange, -1);
            this->curSpriteRange->setPosition(sprite->getPosition());
            //添加相应的炮塔图片
            newSprite = Sprite::createWithSpriteFrameName(sprite->getName());
            newSprite->setPosition(sprite->getPosition());
            newSprite->setScale(0.6);
            newSprite->setName(sprite->getName());
            this->curSprite = newSprite;
            this->addChild(this->curSprite);
        }
    }
    return true;
}

void GameHUD::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));
    Point oldTouchLocation = touch->getPreviousLocationInView();
    oldTouchLocation = Director::getInstance()->convertToGL(oldTouchLocation);
    oldTouchLocation = convertToNodeSpace(oldTouchLocation);
    Point translation = ccpSub(touchLocation, oldTouchLocation);
    if(this->curSprite != NULL)
    {
        Point newPos = this->curSprite->getPosition() + translation;
        this->curSprite->setPosition(newPos);
        this->curSpriteRange->setPosition(newPos);
        DataModel *m = DataModel::getModel();
        Point touchLocationInGameLayer = m->gameLayer->convertTouchToNodeSpace(touch);
        bool isBuildable = m->gameLayer->canBuildOnTilePosition(touchLocationInGameLayer);
        if (isBuildable) {
            this->curSprite->setOpacity(200);
        }
        else
        {
            this->curSprite->setOpacity(50);
        }
    }
}

void GameHUD::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Point touchLocation = this->convertTouchToNodeSpace(touch);
    DataModel *m = DataModel::getModel();
    if(this->curSprite != NULL)
    {
        Rect backgroundRect = Rect(background->getPositionX(),
                                   background->getPositionY(),
                                   background->getContentSize().width * 2,
                                   background->getContentSize().height);
        if(!backgroundRect.containsPoint(touchLocation) &&
           m->gameLayer->canBuildOnTilePosition(touchLocation))
        {
            Point touchLocationInGameLayer = m->gameLayer->convertTouchToNodeSpace(touch);
            m->gameLayer->addTower(touchLocationInGameLayer, this->curSprite->getName());
        }
        this->removeChild(this->curSprite, true);
        this->curSprite = NULL;
        this->removeChild(this->curSpriteRange, true);
        this->curSpriteRange = NULL;
    }
}