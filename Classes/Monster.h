//
//  Monster.h
//  tower
//
//  Created by Yabin Ping on 3/3/15.
//
//

#ifndef __tower__Monster__
#define __tower__Monster__

#include "cocos2d.h"
#include "WayPoint.h"

USING_NS_CC;
enum MonsterType{
    MonsterPink,
    MonsterBlue,
    MonsterGreen,
    MonsterYellow
};

class Monster: public Sprite{
public:
    int curHp;  //怪物的血量
    int value;  //打死怪物能到的价钱
    int moveDuration;   //怪物的速度
    int curWayPoint;
    int tag;
    Sprite *sprite; //怪物的贴图
    std::string sound;  //怪物叫声
    std::string hurtSound;//怪物攻击时的叫声
public:
    virtual bool init();
    WayPoint* getNextWayPoint();
    WayPoint* getCurrentWayPoint();
    CREATE_FUNC(Monster);
};

class MonsterPink: public Monster{
public:
    static Monster* monster();
};


class MonsterBlue: public Monster{
public:
    static Monster* monster();
};


class MonsterGreen: public Monster{
public:
    static Monster* monster();
};


class MonsterYellow: public Monster{
public:
    static Monster* monster();
};


#endif /* defined(__tower__Monster__) */
