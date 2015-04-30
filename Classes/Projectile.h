//
//  Projectile.h
//  Projectile
//
//  Created by Yabin Ping on 1/27/15.
//
//

#ifndef __Projectile__Projectile__
#define __Projectile__Projectile__

#include "cocos2d.h"
USING_NS_CC;

#include "vector"
#include "string"
using namespace std;

enum ProjectileType{
    PArrow,
    PStar,
    PSun,
    PRocket
};


class Projectile : public Sprite
{
public:
    Sprite* sprite; //子弹
    int harm;       // 子弹的伤害值
    ProjectileType type;
    static map<ProjectileType, vector<string> > pAnimation;
public:
    CREATE_FUNC(Projectile);
    void runHitAnimation(Node* target);
    void runHitAnimationFinished(Node* sender);
};


class PArrow : public Projectile
{
public:
    static Projectile* projectile();
    bool virtual init();
};


class PStar : public Projectile
{
public:
    static Projectile* projectile();
    bool virtual init();

};



class PSun : public Projectile
{
public:
    static Projectile* projectile();
    bool virtual init();

};


class PRocket : public Projectile
{
public:
    static Projectile* projectile();
    bool virtual init();

};

#endif /* defined(__Projectile__Projectile__) */
