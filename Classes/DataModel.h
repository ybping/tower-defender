//
//  DataModel.h
//  tower
//
//  Created by Yabin Ping on 1/26/15.
//
//

#ifndef __tower__DataModel__
#define __tower__DataModel__

#include "cocos2d.h"
#include "CCVector.h"
#include "WayPoint.h"
#include "Monster.h"
#include "GameScene.h"
#include "Tower.h"
#include "GameHUD.h"
#include "Projectile.h"
USING_NS_CC;

class DataModel
{
public:
    GameScene *gameLayer;
    bool isGameRunning;
    static DataModel *getModel();
    Vector<WayPoint *> waypoints;
    Vector<Monster *> targets;
    Vector<Wave *> waves;
    Vector<Tower*>  towers;
    GameHUD* gameHUDLayer;
    Vector<Projectile *> projectiles;
    static DataModel *mInstance;
    
private:
    DataModel(){isGameRunning = false;};
    
};


#endif /* defined(__tower__DataModel__) */
