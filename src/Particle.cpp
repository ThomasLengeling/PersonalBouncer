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
        mAudioName = "LinnSnare01.wav";
        
        //seconds
        mTravelTime = 1.5;
        
        mVolumen = 0.5;
        
        mTime = 0;
        mPrevTIme = 0;
        
        mId = 0;
        
        mTranslatePos = ci::vec2(mPos.x, mPos.y);
    }
    
    Particle::Particle(const Particle & p)
    {
        mPos    = p.mPos;
        mVel    = p.mVel;
        mSize   = p.mSize;
        mColor  = p.mColor;
        mAudioName     = p.mAudioName;
        mTravelTime    = p.mTravelTime;
        mVolumen       = p.mVolumen;
        mAudioSource   = p.mAudioSource;
        mAudioSpectral = p.mAudioSpectral;
        mId            = p.mId;
    }
    
    void Particle::update(double time)
    {
        
        mPos  += (mVel * ci::vec3(time));
        
        //ci::vec2 newPos = mTranslatePos;
        //mPos = ci::vec3(newPos.x, newPos.y, 0);
        mTime++;
    }
    
    void Particle::calculateNewVel(ci::vec3 len)
    {
       
        ci::vec3 newVel = ci::vec3( (abs(len)) / ci::vec3(mTravelTime))*ci::vec3(1.0) * glm::sign(mVel); // -1 because we dont count the last velocity fo the collistion detection

       ci::app::console()<<"Counter: "<<mTime<<" - "<<mTravelTime<<" "<<mTravelTime/30.0f<<std::endl;
        
        mTime = 0;
        mVel  = newVel;
        
        ci::vec2 startPos = ci::vec2(mPos.x, mPos.y);
        ci::vec2 newPos = ci::vec2(len.x, len.y);
        
    //    ci::app::console()<<ci::vec2(mTranslatePos)<<" - "<<startPos<<" - "<<newPos<<std::endl;
    //    ci::app::console()<<mTranslatePos.isComplete()<<std::endl;
    
    //   ci::app::timeline().apply( &mTranslatePos, newPos, float(mTravelTime)/30.0f, ci::EaseNone() );
    }
    
    void Particle::setPos(ci::vec3 pos){mPos = pos;}
    void Particle::setVel(ci::vec3 vel){mVel = vel;}
    void Particle::setId(int index){ mId =  index;}
    
    void Particle::setColor(ci::ColorA col){mColor = col;}
    void Particle::setSize(float size){mSize = size;}
    void Particle::setAudioName(std::string name){mAudioName = name;}
    void Particle::setTravelTime(double time){mTravelTime = time;}
    void Particle::setAudioSource(cinder::DataSourceRef source){mAudioSource = source;}
    void Particle::setVolume(double volumen){mVolumen = volumen;}
    void Particle::setAudioSpectrall(const std::vector<float>  & mag){mAudioSpectral = mag;}
    
    
    ci::vec3    Particle::getPos(){return mPos;}
    ci::vec3    Particle::getPrevDir(){return mPrevDir;}
    ci::vec3    Particle::getVel(){return mVel;}
    ci::ColorA  Particle::getColor(){return mColor;}
    float       Particle::getSize(){ return mSize; }
    std::string Particle::getAudioName(){return mAudioName;}
    double      Particle::getTravelTime(){return mTravelTime;}
    cinder::DataSourceRef Particle::getAudioSource(){return mAudioSource;}
    float       Particle::getVolumen(){return mVolumen;}
    std::vector<float> Particle::getSpectral(){return mAudioSpectral;}
    int         Particle::getId(){return mId;}
    
    void Particle::changeDirX()
    {
        mVel.x = mVel.x * -1;
    }
    
    void Particle::changeDirY()
    {
        mVel.y = mVel.y * -1;
    }
    
    void Particle::changeDirZ()
    {
        mVel.z = mVel.z * -1;
    }
}