//
//  LoadScene.cpp
//  tower
//
//  Created by Yabin Ping on 3/6/15.
//
//

#include "LoadScene.h"
#include "MainMenuScene.h"

Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool LoadingScene::init()
{
    if(!Layer::init())
        return false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto backgroundSprite = Sprite::create("scene/background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x,
                                        visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite, -1);
    
    
    std::vector<std::string> plistFiles = {"Arrow", "Star", "Sun", "Rocket"};
    auto cache = SpriteFrameCache::getInstance();
    //读入plist文件
    for (auto str : plistFiles) {
        cache->addSpriteFramesWithFile("tower/" + str + ".plist", "tower/" + str + ".png");
    }
    cache->addSpriteFramesWithFile("object/Monsters.plist", "object/Monsters.png");
    
    plistFiles = {"gamemenu", "stagesbg", "gamepass", "stages"};
    for (auto str : plistFiles) {
        cache->addSpriteFramesWithFile("scene/" + str + ".plist", "scene/" + str + ".png");
    }
    cache->addSpriteFramesWithFile("scene/stagesBG.plist", "scene/stagesBG.png");

    //add sound effect
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/Select.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/PetSound00.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/PetSound01.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/PetSound02.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/PetSound03.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/Perfect.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/Arrow.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/Star.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/Fan.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/Rocket.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/TowerBulid.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.2);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.4);
    // add background music
    if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() == false) {
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/BGMusic.mp3");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BGMusic.mp3",true);
    }

    
    auto closedItem = MenuItemImage::create("menu/closeA.png", "menu/closeB.png",
                                            CC_CALLBACK_1(LoadingScene::menuCloseCallback, this));
    auto closeMenu = Menu::create(closedItem, NULL);
    closeMenu->setPosition(Point(visibleSize.width - closedItem->getContentSize().width / 2,
                                 0 + closedItem->getContentSize().height / 2));
    this->addChild(closeMenu);
    

    
    return true;
}

void LoadingScene::onEnter()
{
    Layer::onEnter();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(LoadingScene::onTouchBegan, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}
bool LoadingScene::onTouchBegan(Touch *touch, Event *event)
{
    MainMenu* mainMenu = MainMenu::create();
    mainMenu->startGame();
}

void LoadingScene::menuCloseCallback(cocos2d::Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Select.mp3");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
}
