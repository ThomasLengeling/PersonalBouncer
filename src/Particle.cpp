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
        mDir   =  ci::vec3(1, 1, 0);
        mPrevDir = mDir;
        mAudioName = "LinnSnare01.wav";
        
        //seconds
        mTravelTime = 1.5;
        
        mVolumen = 0.5;
    }
    
    void Particle::update()
    {
        mPrevDir = mDir;
        mPos += (mVel * mDir);
    }
    
    
    void Particle::calculateNewVel(double len)
    {
        ci::vec3 newVel = ci::vec3(len / mTravelTime) * (glm::sign(mVel * mDir));
        ci::vec3 newVelDir = newVel +  mVel * mDir;
        
        ci::app::console()<<newVel<<" "<<mVel<<" "<<glm::sign(mVel)<<" "<<newVelDir<<std::endl;
        mVel = newVelDir;
    }
    
    void Particle::calculateNewVel(ci::vec3 len)
    {
        ci::vec3 newVel = ci::vec3( (abs(len) - mSize) / ci::vec3(mTravelTime)); // -1 because we dont count the last velocity fo the collistion detection
        
        mVel = newVel;
    }
    
    void Particle::setPos(ci::vec3 pos){mPos = pos;}
    void Particle::setVel(ci::vec3 vel){mVel = vel;}
    void Particle::setDir(ci::vec3 dir){
        if(dir.x == 0)
            dir.x = -1;
        if(dir.y == 0)
            dir.y = 1;
        mDir = dir;
    }
    
    void Particle::setColor(ci::ColorA col){mColor = col;}
    void Particle::setSize(float size){mSize = size;}
    void Particle::setAudioName(std::string name){mAudioName = name;}
    void Particle::setTravelTime(double time){mTravelTime = time;}
    void Particle::setAudioSource(cinder::DataSourceRef source){mAudioSource = source;}
    void Particle::setVolume(double volumen){mVolumen = volumen;}
    void Particle::setAudioSpectrall(const std::vector<float>  & mag){mAudioSpectral = mag;}
    
    ci::vec3    Particle::getPos(){return mPos;}
    ci::vec3    Particle::getDir(){return mDir;}
    ci::vec3    Particle::getPrevDir(){return mPrevDir;}
    ci::vec3    Particle::getVel(){return mVel;}
    ci::ColorA  Particle::getColor(){return mColor;}
    float       Particle::getSize(){ return mSize; }
    std::string Particle::getAudioName(){return mAudioName;}
    double      Particle::getTravelTime(){return mTravelTime;}
    cinder::DataSourceRef Particle::getAudioSource(){return mAudioSource;}
    float       Particle::getVolumen(){return mVolumen;}
    std::vector<float> Particle::getSpectral(){return mAudioSpectral;}
    
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