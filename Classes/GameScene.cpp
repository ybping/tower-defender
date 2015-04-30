#include "GameScene.h"
#include "DataModel.h"
#include <string>
#include "MainMenuScene.h"
#include "GamePassScene.h"
#include "Projectile.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    DataModel *m = DataModel::getModel();
    auto myGameHUD = GameHUD::getInstace();
    layer->addChild(myGameHUD, 1);
    m->gameHUDLayer = myGameHUD;
    m->gameLayer = layer;
    m->isGameRunning = true;
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* stageBG = Sprite::createWithSpriteFrameName("BG1.png");
    stageBG->setPosition(visibleSize.width/2, visibleSize.height/2);
    this->addChild(stageBG, -2);
    // add tile map
    std::string file = "scene/stage01.tmx";
    auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
    this->tileMap = TMXTiledMap::createWithXML(str->getCString(), "scene/");
    this->background = this->tileMap->layerNamed("background");
    this->addChild(this->tileMap, -1);

    this->addWayPoint();
    this->addWaves();
    this->scheduleUpdate();
    this->schedule(schedule_selector(GameScene::gameLogic), 1.0f);
    this->currentLevel = 0;


    return true;
}



void GameScene::gotoPassScene()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/Perfect.mp3");
    auto scene = GamePass::createScene();
    Director::getInstance()->replaceScene(scene);
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BGMusic.mp3",true);
}

void GameScene::FollowPath(Node *sender)
{
    Monster *monster = (Monster *)sender;
    WayPoint *waypoint = monster->getNextWayPoint();
    int moveDuration = monster->moveDuration;
    auto actionMove = MoveTo::create(moveDuration, waypoint->getPosition());
    auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameScene::FollowPath));
    monster->stopAllActions();
    monster->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(("sound/" + monster->sound).c_str());
}

void GameScene::addWaves()
{
    DataModel *m = DataModel::getModel();
    Wave *wave = NULL;
    wave = Wave::create()->initWithMonster(MonsterType::MonsterBlue, 300.0, 2);
    m->waves.pushBack(wave);
    wave = NULL;
    
    wave = Wave::create()->initWithMonster(MonsterType::MonsterPink, 500.0, 3);
    m->waves.pushBack(wave);
    wave = NULL;

    wave = Wave::create()->initWithMonster(MonsterType::MonsterYellow, 700.0, 2);
    m->waves.pushBack(wave);
    wave = NULL;

    
    wave = Wave::create()->initWithMonster(MonsterType::MonsterGreen, 1000.0, 4);
    m->waves.pushBack(wave);
    wave = NULL;
}

void GameScene::addWayPoint()
{
    DataModel *m = DataModel::getModel();
    //get waypoints from tile map
    auto *objects = this->tileMap->objectGroupNamed("Objects");
    WayPoint *wp = NULL;
    
    std::string stringWithFormat = "Waypoint";
    int wayPointCounter = 0;
    ValueMap wayPoint;
    wayPoint = objects->objectNamed(stringWithFormat + std::to_string(wayPointCounter));
    while (wayPoint.begin() != wayPoint.end()) {
        int x = wayPoint.at("x").asInt();
        int y = wayPoint.at("y").asInt();
        wp = WayPoint::create();
        wp->setPosition(Point(x,y));
        m->waypoints.pushBack(wp);
        wayPointCounter++;
        wayPoint = objects->objectNamed(stringWithFormat + std::to_string(wayPointCounter));
    }
    wp = NULL;
}

void GameScene::addTarget()
{
    DataModel *m = DataModel::getModel();
    Wave *wave = this->getCurrentWave();
    if(wave->totalMonsters <= 0)
        return ;
    wave->totalMonsters--;
    Monster *target = NULL;
    switch (wave->monsterType) {
        case MonsterGreen:
        {
            target = MonsterGreen::monster();
            break;
        }
        case MonsterBlue:
        {
            target = MonsterBlue::monster();
            break;
        }
        case MonsterPink:
        {
            target = MonsterPink::monster();
            break;
        }
        case MonsterYellow:
        {
            target = MonsterYellow::monster();
            break;
        }
        default:
            break;
    }
    assert(target != NULL);
    WayPoint *waypoint = target->getCurrentWayPoint();
    target->setPosition(waypoint->getPosition());
    waypoint = target->getNextWayPoint();
    this->addChild(target, 1);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(("sound/" + target->sound).c_str());
    int MoveDuration = target->moveDuration;
    auto actionMove = MoveTo::create(MoveDuration, waypoint->getPosition());
    auto actionMoveDone = CallFuncN::create(this,
                                            callfuncN_selector(GameScene::FollowPath));
    target->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
    target->tag = 1;
    m->targets.pushBack(target);
}

void GameScene::gameLogic(float dt)
{
    Wave *wave = this->getCurrentWave();
    static double lastTimeTargetAdded = 0;
    
    double now = time(NULL)*1.0;
    if(lastTimeTargetAdded == 0 || now - lastTimeTargetAdded >= wave->spwanRate / 1000.0)
    {
        this->addTarget();
        lastTimeTargetAdded = now;
    }
    this->getNextWave();
}

void GameScene::update(float dt)
{
    DataModel *m = DataModel::getModel();
    Vector<Projectile*> projectileToDelete;
    for(int i = 0; i < m->projectiles.size(); ++i)
    {
        auto projectile = m->projectiles.at(i);
        auto projectileSprite = projectile->sprite;
        Rect projectileRect = Rect(projectile->getPositionX() - projectileSprite->getContentSize().width / 2,
                                   projectile->getPositionY() - projectileSprite->getContentSize().height / 2,
                                   projectileSprite->getContentSize().width,
                                   projectileSprite->getContentSize().height);
        Vector<Monster *> targetsToDelete;
        for(auto target : m->targets)
        {
            Rect targetRect = Rect(target->getPositionX() - target->getContentSize().width / 2,
                                    target->getPositionY() - target->getContentSize().height / 2,
                                    target->getContentSize().width,
                                    target->getContentSize().height);
            if(projectileRect.intersectsRect(targetRect))
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(("sound/" + target->hurtSound).c_str());
                projectile->runHitAnimation(target);
                projectileToDelete.pushBack(projectile);
                Monster *monster = target;
                monster->curHp -= projectile->harm;
                if(monster->curHp <= 0)
                {
                    targetsToDelete.pushBack(monster);
                }
                break;
            }
        }
        for(auto target : targetsToDelete)
        {
            m->targets.eraseObject(target);
            this->removeChild(target, true);
        }

    }
    for(auto projectile : projectileToDelete)
    {
        m->projectiles.eraseObject(projectile);
        this->removeChild(projectile, true);
        
    }
    if(this->gamePassed())
    {
        this->gotoPassScene();
    }
}


Wave* GameScene::getCurrentWave()
{
    DataModel *m = DataModel::getModel();
    Wave *wave = m->waves.at(this->currentLevel);
    return wave;
}

Wave* GameScene::getNextWave()
{
    DataModel *m = DataModel::getModel();
    this->currentLevel ++;
    if (this->currentLevel >= m->waves.size()) {
        this->currentLevel = 0;
    }
    Wave *wave = m->waves.at(this->currentLevel);
    return wave;
}
Point GameScene::tileCoordForPosition(Point position)
{
    int x = position.x / this->tileMap->getTileSize().width;
    int y = ((this->tileMap->getMapSize().height * this->tileMap->getTileSize().height) - position.y) /
            this->tileMap->getTileSize().height;
    return Point(x,y);
}


bool GameScene::canBuildOnTilePosition(Point pos)
{
    Point towerLoc = this->tileCoordForPosition(pos);
    int tileGid = this->background->getTileGIDAt(towerLoc);
    Value props = this->tileMap->getPropertiesForGID(tileGid);
   
    if(props.isNull())
    {
        return true;
    }
    ValueMap map = props.asValueMap();
    bool buildable = true;
    if(map.size() != 0)
        buildable = map.at("buildable").asBool();
    return buildable;
}

void GameScene::addTower(Point pos, std::string towerType)
{
    DataModel *m = DataModel::getModel();
    Tower *target = NULL;
    bool buildable = canBuildOnTilePosition(pos);
    if (buildable) {
        Point towerLoc = this->tileCoordForPosition(pos);
        towerType = towerType.substr(0, 3);
        if (towerType == "Arr") {
            target = TArrow::tower();
        }else if (towerType == "Sta"){
            target = TStar::tower();
        }else if (towerType == "Sun"){
            target = TSun::tower();
        }else if (towerType == "Roc"){
            target = TRocket::tower();
        }
        else{
            return ;
        }
        target->setPosition(Point(towerLoc.x * 32 + 16,
                                  this->tileMap->getContentSize().height - towerLoc.y * 32 - 16));
        this->addChild(target, 1);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/TowerBulid.mp3");
        target->setTag(1);
        m->towers.pushBack(target);
    }
    else
    {
        CCLog("Tile Not Buildable");
    }
}

bool GameScene::gamePassed()
{
    DataModel *m = DataModel::getModel();
    if(m->targets.size() > 0)
        return false;
    for (auto wave : m->waves) {
        if (wave->totalMonsters > 0) {
            return false;
        }
    }
    return true;
}

void GameScene::runHitAnimation(Projectile *projectile, Point postion)
{
    vector<string> pAnimation = Projectile::pAnimation[projectile->type];
    auto sprite = Sprite::createWithSpriteFrameName(pAnimation[1]);
    SpriteBatchNode *spriteBatch = NULL;
    spriteBatch = SpriteBatchNode::create("tower/"+ pAnimation[0]);
    
    spriteBatch->addChild(sprite);
    spriteBatch->setPosition(postion);
    this->addChild(spriteBatch, 0);
    
    auto cache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames(pAnimation.size() - 1);
    for(int i = 1; i < pAnimation.size(); i++)
    {
        auto frame = cache->getSpriteFrameByName(pAnimation[i]);
        animFrames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    sprite->runAction(Sequence::create(Animate::create(animation),
                                       CallFuncN::create(spriteBatch, callfuncN_selector(GameScene::runHitAnimationFinished)), NULL));
}

void GameScene::runHitAnimationFinished(Node* pSender)
{
    pSender->getParent()->removeChild(pSender, true);
}
