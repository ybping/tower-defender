//
//  Tower.h
//  tower
//
//  Created by Yabin Ping on 1/27/15.
//
//

#ifndef __tower__Tower__
#define __tower__Tower__
#include "cocos2d.h"
#include "Monster.h"
#include "Projectile.h"

enum TowerType{
    TArrow,
    TStar,
    TSun,
    TRocket,
};

class Tower: public Sprite{
public:
    int range;
    Sprite *deck;   //炮台
    Sprite *sprite; //炮塔
    Monster* target;
    Sprite* selSpriteRange;
    Projectile *curProjectile;
    Projectile* (*projectile)();
    std::string sound;
    int bulletNums = 1; //炮塔每次射击射出的子弹数量
public:
    Monster* getClosesTarget();
    void towerLogic(float dt);
    void finishFiring();
    void monsterMoveFinished(Node* sender);
    CREATE_FUNC(Tower);

};


class TArrow:public Tower
{
public:
    static Tower* tower();
    bool virtual init();

};

class TStar:public Tower
{
public:
    static Tower* tower();
    bool virtual init();
    
};

class TSun:public Tower
{
public:
    static Tower* tower();
    bool virtual init();
    
};

class TRocket:public Tower
{
public:
    static Tower* tower();
    bool virtual init();
    
};
#endif /* defined(__tower__Tower__) */
