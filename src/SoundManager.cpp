//
//  SoundManager.cpp
//  PersonalBouncer
//
//  Created by tom on 11/29/15.
//
//

#include "SoundManager.h"


cinder::DataSourceRef SoundManager::getDrumAudio(std::string name )
{
    return cinder::app::loadAsset("Linn Drum/"+name);
}

cinder::DataSourceRef SoundManager::getKickAudio(std::string name )
{
    return cinder::app::loadAsset("Linn Drum/"+name);
}