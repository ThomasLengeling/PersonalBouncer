//
//  SoundManager.hpp
//  PersonalBouncer
//
//  Created by tom on 11/29/15.
//
//

#pragma once

#include "cinder/app/App.h"

class SoundManager{
public:
    static cinder::DataSourceRef getDrumAudio(std::string name );
    static cinder::DataSourceRef getKickAudio(std::string name );
private:

};

