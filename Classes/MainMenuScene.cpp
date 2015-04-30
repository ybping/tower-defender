#include "MainMenuScene.h"
#include "GameScene.h"
#include "DataModel.h"
USING_NS_CC;

Scene* MainMenu::createScene(cocos2d::CCRenderTexture* sqr)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    //使用Game界面中截图的sqr纹理图片创建Sprite，并将背景Sprite添加到场景层中
    //得到窗口的大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Sprite *background = Sprite::createWithTexture(sqr->getSprite()->getTexture());
    background->setPosition(visibleSize.width/2,visibleSize.height/2); //放置位置,这个相对于中心位置。
    background->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同
    background->setColor(cocos2d::ccGRAY); //图片颜色变灰色
    scene->addChild(background, -1);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Sprite::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //Add menu background
    auto menuBgSprite = Sprite::createWithSpriteFrameName("menu_bg.png");
    menuBgSprite->setPosition(Point(visibleSize.width / 2 + origin.x,
                                        visibleSize.height / 2 + origin.y));
    this->addChild(menuBgSprite);
    
    //关卡选择按钮
    auto playNormal = Sprite::createWithSpriteFrameName("menu_quit_normal_CN.png");
    auto playSelected = Sprite::createWithSpriteFrameName("menu_quit_pressed_CN.png");
    auto playItem = MenuItemSprite::create(playNormal, playSelected, nullptr,  CC_CALLBACK_1(MainMenu::gotoGameScene, this));
   
    //重新开始
    // Font Item
    auto restartNormal = Sprite::createWithSpriteFrameName("menu_restart_normal_CN.png");
    auto restartSelected = Sprite::createWithSpriteFrameName("menu_restart_pressed_CN.png");
    auto restartItem = MenuItemSprite::create(restartNormal, restartSelected, nullptr,  CC_CALLBACK_1(MainMenu::gotoRestartScene, this));
    
    //继续游戏
    
    // Font Item
    auto resumeNormal = Sprite::createWithSpriteFrameName("menu_resume_normal_CN.png");
    auto resumeSelected = Sprite::createWithSpriteFrameName("menu_resume_pressed_CN.png");
    auto resumeItem = MenuItemSprite::create(resumeNormal, resumeSelected, nullptr,  CC_CALLBACK_1(MainMenu::gotoContinueScene, this));
    
    auto menu = Menu::create(playItem, restartItem, resumeItem, NULL);
    menu->alignItemsVerticallyWithPadding(15);
    this->addChild(menu);

    auto closedItem = MenuItemImage::create("menu/closeA.png", "menu/closeB.png",
                                           CC_CALLBACK_1(MainMenu::closeGame, this));
    auto closeMenu = Menu::create(closedItem, NULL);
    closeMenu->setPosition(Point(visibleSize.width - closedItem->getContentSize().width / 2,
                                 0 + closedItem->getContentSize().height / 2));
    this->addChild(closeMenu);
    
    return true;
}

void MainMenu::startGame()
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BGMusic01.mp3",true);
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.9f);
}

bool MainMenu::isGameStarted()
{
    DataModel *m = DataModel::getModel();
    return m->isGameRunning;
}

void MainMenu::gotoGameScene(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Select.mp3");
    if(this->isGameStarted())
    {
        gotoRestartScene(pSender);
    }
    else
    {
        startGame();
    }
}

void MainMenu::gotoContinueScene(cocos2d::Ref *pSender)
{
    if(this->isGameStarted()){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Select.mp3");
        Director::getInstance()->popScene();
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BGMusic01.mp3",true);
    }
    else{
        this->startGame();
    }
}


void MainMenu::gotoRestartScene(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Select.mp3");
    if (this->isGameStarted()) {
        // pop the current pause scene
        Director::getInstance()->popScene();
        GameHUD::mInstance = NULL;
        DataModel::mInstance = NULL;
    }
    this->startGame();
}

void MainMenu::closeGame(cocos2d::Ref *pSender)
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