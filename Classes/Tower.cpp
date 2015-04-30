//
//  Tower.cpp
//  tower
//
//  Created by Yabin Ping on 1/27/15.
//
//

#include "Tower.h"
#include "DataModel.h"
Monster* Tower::getClosesTarget()
{
    Monster *closestMonster = NULL;
    double minDistance = 1 << 20;
    DataModel *m = DataModel::getModel();
    for(auto target : m->targets)
    {
        Monster *creep = (Monster *)target;
        double curDistance = ccpDistance(this->getPosition(), creep->getPosition());
        if(curDistance < minDistance){
            closestMonster = creep;
            minDistance = curDistance;
        }
    }
    if(minDistance < this->range)
        return closestMonster;
    return NULL;
}

void Tower::finishFiring()
{
    DataModel *m = DataModel::getModel();
    if(this->target != NULL && this->target->curHp > 0)
    {
       
        //射击方向向量
        Point shootVector = this->target->getPosition() - this->getPosition();
        //向量标准化，长度为1
        Point normalizedShootVector = ccpNormalize(shootVector);
        // 计算旋转的弧度
        float shootAngle = atan2(normalizedShootVector.y, -normalizedShootVector.x);
        //讲弧度转化为角度
        float degree = CC_RADIANS_TO_DEGREES(shootAngle);
        //移动长度向量
        Point overshotVector = normalizedShootVector * 320;
        //超出屏幕的点
        Point offscreenPoint = (this->getPosition() + overshotVector);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(("sound/" + this->sound).c_str());
       
        Point tmp = offscreenPoint;
        // 这里子弹的数目默认为奇数，各颗子弹相隔15度数
        int alph = 15;
        for(int i = -this->bulletNums / 2; i <= this->bulletNums / 2; ++i)
        {
            this->curProjectile = this->projectile();
            this->curProjectile->setPosition(this->getPosition());
            this->getParent()->addChild(this->curProjectile, 1);
            m->projectiles.pushBack(this->curProjectile);
            offscreenPoint = tmp;
            offscreenPoint.rotate(this->getPosition(), CC_DEGREES_TO_RADIANS(i*alph));
            this->curProjectile->runAction(Sequence::create(RotateTo::create(0.0f, degree - 90 - i*alph),
                                                         MoveTo::create(1.0f, offscreenPoint),
                                                         CallFuncN::create(this, callfuncN_selector(Tower::monsterMoveFinished)), NULL));
            this->curProjectile->setTag(2);
            this->curProjectile = NULL;
        }
    }
}

void Tower::monsterMoveFinished(cocos2d::Node *sender)
{
    DataModel *m = DataModel::getModel();
    Sprite *sprite = (Sprite*)sender;
    this->getParent()->removeChild(sprite, true);
    m->projectiles.eraseObject((Projectile*)sprite);
}

void Tower::towerLogic(float dt)
{
    this->target = this->getClosesTarget();
    if(this->target != NULL)
    {
        //调整炮塔的方向对准怪物，射击方向向量
        Point shootVector = this->target->getPosition() - this->getPosition();
        //向量标准化，长度为1
        Point normalizedShootVector = ccpNormalize(shootVector);
        // 计算旋转的弧度
        float shootAngle = atan2(normalizedShootVector.y, -normalizedShootVector.x);
        //讲弧度转化为角度
        float degree = CC_RADIANS_TO_DEGREES(shootAngle);
        // 匀速旋转，这里设置旋转速度为2pi(rad/s)
        float rotateSpeed = 2 * M_PI;
        // 那么旋转1弧度的时间为
        float rotate1RadTime = 1.0 / rotateSpeed;
        // 则旋转时长为
        float rotateDuration = fabs(shootAngle * rotate1RadTime);
        
        this->runAction(Sequence::create(RotateTo::create(rotateDuration, degree - 90), CallFunc::create(this, callfunc_selector(Tower::finishFiring)), NULL));
    }
}

Tower* TArrow::tower()
{
    Tower* tower = Tower::create();
    tower->deck = Sprite::createWithSpriteFrameName("Arrow-13.png");
    tower->addChild(tower->deck);
    //设置Sprite动画
    tower->sprite = Sprite::createWithSpriteFrameName("Arrow31.png");
    auto spriteBatch = SpriteBatchNode::create("tower/Arrow.png");
    spriteBatch->addChild(tower->sprite);
    tower->addChild(spriteBatch, 0);

    auto cache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames(3);
    char str[100] = {0};
    for(int i = 1; i <= 3; i++)
    {
        // Obtain frames by alias name
        sprintf(str, "Arrow3%d.png", i);
        auto frame = cache->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    tower->sprite->runAction(RepeatForever::create(Animate::create(animation)));
    tower->setScale(0.5);
    tower->range = 200;
    tower->projectile = PArrow::projectile;
    tower->schedule(schedule_selector(Tower::towerLogic), 0.2);
    tower->sound = "Arrow.mp3";
    tower->bulletNums = 3;
    return tower;
}

bool TArrow::init()
{
    if(!Sprite::init())
        return false;
    return true;
}


Tower* TStar::tower()
{
    Tower* tower = Tower::create();
    tower->deck = Sprite::createWithSpriteFrameName("Star-13.png");
    tower->addChild(tower->deck);
    //设置Sprite动画
    tower->sprite = Sprite::createWithSpriteFrameName("Star31.png");
    auto spriteBatch = SpriteBatchNode::create("tower/Star.png");
    spriteBatch->addChild(tower->sprite);
    tower->addChild(spriteBatch, 0);
    
    auto cache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames(3);
    char str[100] = {0};
    for(int i = 1; i <= 3; i++)
    {
        // Obtain frames by alias name
        sprintf(str, "Star3%d.png", i);
        auto frame = cache->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    tower->sprite->runAction(RepeatForever::create(Animate::create(animation)));
    tower->setScale(0.5);
    tower->range = 200;
    tower->projectile = PStar::projectile;
    tower->schedule(schedule_selector(Tower::towerLogic), 0.2);
    tower->sound = "Star.mp3";
    return tower;
}

bool TStar::init()
{
    if(!Sprite::init())
        return false;
    return true;
}

Tower* TSun::tower()
{
    Tower* tower = Tower::create();
    tower->deck = Sprite::createWithSpriteFrameName("Sun-13.png");
    tower->addChild(tower->deck);
    //设置Sprite动画
    tower->sprite = Sprite::createWithSpriteFrameName("Sun00.png");
    auto spriteBatch = SpriteBatchNode::create("tower/Sun.png");
    spriteBatch->addChild(tower->sprite);
    tower->addChild(spriteBatch, 0);
    
    auto cache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames(3);
    char str[100] = {0};
    for(int i = 1; i <= 3; i++)
    {
        // Obtain frames by alias name
        sprintf(str, "Sun%d1.png", i);
        auto frame = cache->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    tower->sprite->runAction(RepeatForever::create(Animate::create(animation)));
    tower->setScale(0.5);
    tower->range = 200;
    tower->projectile = PSun::projectile;
    tower->schedule(schedule_selector(Tower::towerLogic), 0.2);
    tower->sound = "Fan.mp3";
    return tower;
}

bool TSun::init()
{
    if(!Sprite::init())
        return false;
    return true;
}

Tower* TRocket::tower()
{
    
    Tower* tower = Tower::create();
    tower->deck = Sprite::createWithSpriteFrameName("Rocket-13.png");
    tower->addChild(tower->deck);
    //设置Sprite动画
    tower->sprite = Sprite::createWithSpriteFrameName("Rocket00.png");
    auto spriteBatch = SpriteBatchNode::create("tower/Rocket.png");
    spriteBatch->addChild(tower->sprite);
    tower->addChild(spriteBatch, 0);
    
    auto cache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames(3);
    char str[100] = {0};
    for(int i = 1; i <= 3; i++)
    {
        // Obtain frames by alias name
        sprintf(str, "Rocket3%d.png", i);
        auto frame = cache->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    tower->sprite->runAction(RepeatForever::create(Animate::create(animation)));
    tower->setScale(0.5);
    tower->range = 200;
    tower->projectile = PRocket::projectile;
    tower->schedule(schedule_selector(Tower::towerLogic), 0.2);
    tower->sound = "Rocket.mp3";
    return tower;
}

bool TRocket::init()
{
    if(!Sprite::init())
        return false;
    return true;
}

