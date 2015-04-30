#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Monster.h"
#include "WayPoint.h"
#include "Wave.h"
#include "GameHUD.h"
#include "Tower.h"
#include "SimpleAudioEngine.h"

class GameScene : public cocos2d::Layer
{
private:
    cocos2d::TMXTiledMap *tileMap;
    cocos2d::TMXLayer *background;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    int currentLevel;   //关卡参数
    
    void addWayPoint(); //路径参数
    void addWaves();    //几波怪物
    void FollowPath(Node *sender);  //怪物路径
    void gameLogic(float dt);
    void addTarget();   //添加怪物
    virtual void update(float dt);
    Wave* getCurrentWave(); //更新怪物波数
    Wave* getNextWave();
    bool gamePassed();  //判断是否通关
    
    // Game HUD
    void addTower(Point pos, std::string towerType);
    Point tileCoordForPosition(Point position);
    bool canBuildOnTilePosition(Point pos);
    Point boundLayerPos(Point newPos);
    
    //调到通关界面
    void gotoPassScene();
    
    //子弹爆炸效果
    void runHitAnimation(Projectile *projectile, Point postion);
    void runHitAnimationFinished(Node* pSender);
    
};

#endif // __HELLOWORLD_SCENE_H__
