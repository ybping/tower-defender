//
//  Projectile.cpp
//  tower
//
//  Created by Yabin Ping on 1/27/15.
//
//

#include "Projectile.h"

 map<ProjectileType, vector<string> > Projectile::pAnimation = {
    make_pair(ProjectileType::PArrow, vector<string>{"Arrow.png","PArrow01.png","PArrow02.png"}),
    make_pair(ProjectileType::PStar, vector<string>{"Star.png",
        "PStar-11.png","PStar-12.png","PStar-13.png","PStar-14.png","PStar-15.png","PStar-16.png"}),
    make_pair(ProjectileType::PSun, vector<string>{"Sun.png","PSun01.png","PSun02.png"}),
    make_pair(ProjectileType::PRocket, vector<string>{"Rocket.png",
        "PRocket-11.png","PRocket-12.png","PRocket-13.png","PRocket-14.png","PRocket-15.png","PRocket-16.png"}),
};


void Projectile::runHitAnimation(Node* target)
{
    vector<string> pAnimation = Projectile::pAnimation[this->type];
    auto sprite = Sprite::createWithSpriteFrameName(pAnimation[1]);
    SpriteBatchNode *spriteBatch = NULL;
    spriteBatch = SpriteBatchNode::create("tower/"+ pAnimation[0]);
    
    spriteBatch->addChild(sprite);
    spriteBatch->setPosition(target->getPosition());
    this->getParent()->addChild(spriteBatch, 0);
    
    auto cache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames(pAnimation.size() - 1);
    for(int i = 1; i < pAnimation.size(); i++)
    {
        auto frame = cache->getSpriteFrameByName(pAnimation[i]);
        animFrames.pushBack(frame);
    }
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    sprite->runAction(Sequence::create(Animate::create(animation),
                                       CallFuncN::create(this, callfuncN_selector(Projectile::runHitAnimationFinished)), NULL));
}

void Projectile::runHitAnimationFinished(Node* pSender)
{
    pSender->getParent()->removeChild(pSender, true);
}


Projectile* PArrow::projectile()
{
    Projectile* projectile = Projectile::create();
    projectile->sprite = Sprite::createWithSpriteFrameName("PArrow31.png");
    projectile->addChild(projectile->sprite);
    projectile->setScale(0.5);
    projectile->harm = 3;
    projectile->type = ProjectileType::PArrow;
    return projectile;
}

bool PArrow::init()
{
    if(!Sprite::init())
        return false;
    return true;
}


Projectile* PStar::projectile()
{
    Projectile* projectile = Projectile::create();
    projectile->sprite = Sprite::createWithSpriteFrameName("PStar31.png");
    projectile->addChild(projectile->sprite);
    projectile->setScale(0.5);
    projectile->harm = 3;
    projectile->type = ProjectileType::PStar;
    auto repeatAction = RepeatForever::create(RotateBy::create(1.0f, 360) );
    projectile->runAction(repeatAction);
    return projectile;
}

bool PStar::init()
{
    if(!Sprite::init())
        return false;
    return true;
}


Projectile* PSun::projectile()
{
    
    Projectile* projectile = Projectile::create();
    projectile->sprite = Sprite::createWithSpriteFrameName("PSun31.png");
    projectile->addChild(projectile->sprite);
    projectile->setScale(0.5);
    projectile->harm = 3;
    projectile->type = ProjectileType::PSun;
    auto repeatAction = RepeatForever::create(RotateBy::create(1.0f, 360) );
    projectile->runAction(repeatAction);
    return projectile;
}

bool PSun::init()
{
    if(!Sprite::init())
        return false;
    return true;
}


Projectile* PRocket::projectile()
{
    
    Projectile* projectile = Projectile::create();
    projectile->sprite = Sprite::createWithSpriteFrameName("PRocket31.png");
    projectile->addChild(projectile->sprite);
    projectile->setScale(0.5);
    projectile->harm = 3;
    projectile->type = ProjectileType::PRocket;
    return projectile;
}

bool PRocket::init()
{
    if(!Sprite::init())
        return false;
    return true;
}


