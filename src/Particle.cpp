//
//  Particle.cpp
//  PersonalBouncer
//
//  Created by thomas on 11/19/15.
//
//

#include "Particle.h"

namespace physics{

    Particle::Particle()
    {
        mSize  =  1.0f;
        mVel   =  ci::vec3(0, 0.1, 0);
        mColor =  ci::ColorA(0, 1, 0, 1);
        mDir   =  ci::vec3(1, 1, 1);
    }
    
    void Particle::update()
    {
        mPos += mVel * mDir;
    }
    
    
    void Particle::setPos(ci::vec3 pos){mPos = pos;}
    void Particle::setVel(ci::vec3 vel){mVel = vel;}
    void Particle::setColor(ci::ColorA col){mColor = col;}
    void Particle::setSize(float size){mSize = size;}
    
    ci::vec3    Particle::getPos(){return mPos;}
    ci::vec3    Particle::getVel(){return mVel;}
    ci::ColorA  Particle::getColor(){return mColor;}
    float       Particle::getSize(){ return mSize; }
    
    
    
    void Particle::changeDirX()
    {
        mDir.x = mDir.x * -1;
    }
    
    void Particle::changeDirY()
    {
        mDir.y = mDir.y * -1;
    }
    
    void Particle::changeDirZ()
    {
        mDir.z = mDir.z * -1;
    }
}