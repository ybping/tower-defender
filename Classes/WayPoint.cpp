//
//  WayPoint.cpp
//  tower
//
//  Created by Yabin Ping on 1/26/15.
//
//

#include "WayPoint.h"
bool WayPoint::init()
{
    if(!Node::init())
    {
        return false;
    }
    return true;
    
}