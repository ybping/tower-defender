//
//  WayPoint.h
//  tower
//
//  Created by Yabin Ping on 1/26/15.
//
//

#ifndef __tower__WayPoint__
#define __tower__WayPoint__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
class WayPoint:public Node
{
public:
    virtual bool init();
    CREATE_FUNC(WayPoint);
};


#endif /* defined(__tower__WayPoint__) */
