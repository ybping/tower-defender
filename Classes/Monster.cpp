//
//  Monster.cpp
//  tower
//
//  Created by Yabin Ping on 3/3/15.
//
//

#include "Monster.h"
#include "WayPoint.h"
#include "DataModel.h"

bool Monster::init()
{
    if(!Sprite::init())
        return false;
    return true;
}


Monster* MonsterPink::monster()
{
    auto monster = Monster::create();
    monster->sprite = Sprite::createWithSpriteFrameName("land_pink01.png");
    monster->addChild(monster->sprite, 0);
    monster->curHp = 60;
    monster->moveDuration = 3;
    monster->value = 10;
    monster->curWayPoint = 0;
    monster->sound = "PetSound00.mp3";
    monster->hurtSound = "PetSound000.mp3";
    return monster;
}

Monster* MonsterBlue::monster()
{
    auto monster = Monster::create();
    monster->sprite = Sprite::createWithSpriteFrameName("fly_blue01.png");
    monster->addChild(monster->sprite, 0);
    monster->curHp = 60;
    monster->moveDuration = 3;
    monster->value = 10;
    monster->curWayPoint = 0;
    monster->sound = "PetSound01.mp3";
    monster->hurtSound = "PetSound011.mp3";
    return monster;
}

Monster* MonsterGreen::monster()
{
    auto monster = Monster::create();
    monster->sprite = Sprite::createWithSpriteFrameName("fat_green01.png");
    monster->addChild(monster->sprite, 0);
    monster->curHp = 60;
    monster->moveDuration = 3;
    monster->value = 10;
    monster->curWayPoint = 0;
    monster->sound = "PetSound02.mp3";
    monster->hurtSound = "PetSound022.mp3";
    return monster;
}

Monster* MonsterYellow::monster()
{
    auto monster = Monster::create();
    monster->sprite = Sprite::createWithSpriteFrameName("fly_yellow01.png");
    monster->addChild(monster->sprite, 0);
    monster->curHp = 60;
    monster->moveDuration = 3;
    monster->value = 10;
    monster->curWayPoint = 0;
    monster->sound = "PetSound03.mp3";
    monster->hurtSound = "PetSound033.mp3";
    return monster;
}
WayPoint* Monster::getCurrentWayPoint()
{
    DataModel* m = DataModel::getModel();
    WayPoint* wayPoint = (WayPoint*)m->waypoints.at(this->curWayPoint);
    return wayPoint;
}

WayPoint* Monster::getNextWayPoint()
{
    DataModel* m = DataModel::getModel();
    this->curWayPoint = (this->curWayPoint + 1) % (m->waypoints.size());
    CCLOG("curWayPoint%d", this->curWayPoint);
    WayPoint* wayPoint = (WayPoint *)m->waypoints.at(curWayPoint);
    return wayPoint;
}


