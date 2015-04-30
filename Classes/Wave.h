//
//  Wave.h
//  tower
//
//  Created by Yabin Ping on 1/26/15.
//
//

#ifndef __tower__Wave__
#define __tower__Wave__

#include "cocos2d.h"
#include "Monster.h"

USING_NS_CC;

class Wave: public Node{
public:
    Point position;
    int totalMonsters;
    double spwanRate;
    MonsterType monsterType;

public:
    virtual bool init();
    Wave* initWithMonster(MonsterType monsterType, double spawnRate, int totalMonsters);
    CREATE_FUNC(Wave);
};

#endif /* defined(__tower__Wave__) */
