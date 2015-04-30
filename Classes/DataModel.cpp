//
//  DataModel.cpp
//  tower
//
//  Created by Yabin Ping on 1/26/15.
//
//

#include "DataModel.h"

DataModel* DataModel::mInstance = NULL;
DataModel* DataModel::getModel()
{
    if(mInstance == NULL){
        mInstance = new DataModel();
    }
    return mInstance;
}