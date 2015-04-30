//
//  Wave.cpp
//  tower
//
//  Created by Yabin Ping on 1/26/15.
//
//

#include "Wave.h"

bool Wave::init()
{
    if(!Node::init())
    {
        return false;
    }
    return true;
}

Wave* Wave::initWithMonster(MonsterType monsterType, double spawnRate, int totalMonsters)
{
    this->monsterType = monsterType;
    this->spwanRate = spawnRate;
    this->totalMonsters = totalMonsters;
    return this;
}