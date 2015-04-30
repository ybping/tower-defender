#include "GamePassScene.h"
#include "LoadScene.h"
#include "GameHUD.h"
#include "DataModel.h"

USING_NS_CC;

Scene* GamePass::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GamePass::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePass::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("scene/background.png");
    background->setPosition(Point(visibleSize.width / 2 + origin.x,
                                        visibleSize.height / 2 + origin.y));
    this->addChild(background, -1);

    auto backItem = MenuItemImage::create("menu/backA.png", "menu/backB.png",
                                          CC_CALLBACK_1(GamePass::gotoMainMenuScene, this));
    
    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Point(visibleSize.width - backItem->getContentSize().width / 2,
                            visibleSize.height - backItem->getContentSize().height / 2));
    this->addChild(menu);

    auto backgroundSprite = Sprite::createWithSpriteFrameName("win_bg.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x,
                                        visibleSize.height / 2 + origin.y  - 20));
    this->addChild(backgroundSprite, -1);
    
    char name[100];
    for (int i = 1;  i <= 3; ++i) {
        sprintf(name, "gainhonor_%d.png", i);
        auto honorSprite = Sprite::createWithSpriteFrameName(name);
        honorSprite->setPosition(Point(visibleSize.width / 2 + origin.x + (i - 2) * 120,
                                            visibleSize.height / 2 + origin.y));
        this->addChild(honorSprite);
    }
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Perfect.mp3");
    return true;
}

void GamePass::gotoMainMenuScene(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Select.mp3");
    auto scene = LoadingScene::createScene();
    Director::getInstance()->replaceScene(scene);
    DataModel::mInstance->isGameRunning = false;
    GameHUD::mInstance = NULL;
    DataModel::mInstance = NULL;
}