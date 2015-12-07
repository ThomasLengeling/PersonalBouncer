//
//  Particle.hpp
//  PersonalBouncer
//
//  Created by thomas on 11/19/15.
//
//

#pragma once

#include <stdio.h>
#include "cinder/Timeline.h"

namespace physics {
    
    class Particle;
    typedef std::shared_ptr<Particle> ParticleRef;
    
    class Particle{
    public:
        Particle();
        Particle(const Particle & p);
        
        static ParticleRef create(){return std::make_shared<Particle>();}
        
        void update(double time);
        
        void calculateNewVel(double len);
        void calculateNewVel(ci::vec3 length);
        
        void setPos(ci::vec3 pos);
        void setVel(ci::vec3 vel);
        void setColor(ci::ColorA col);
        void setSize(float size);
        void setAudioName(std::string name);
        void setAudioSource(cinder::DataSourceRef source);
        void setTravelTime(double time);
        void setVolume(double volumen);
        void setId(int index);
        void setCounter(int counter){mTime =counter;}
        
        void setStartPosition(ci::vec2 start){mTranslatePos = ci::vec2(start.x, start.y);}
        
        void setAudioSpectrall(const std::vector<float>  & mag);
        
        
        bool        isTransitionComplete(){return mTranslatePos.isComplete();}
        
        ci::vec3    getPos();
        ci::vec3    getPrevDir();
        ci::vec3    getVel();
        ci::ColorA  getColor();
        float       getSize();
        std::string getAudioName();
        double      getTravelTime();
        cinder::DataSourceRef  getAudioSource();
        std::vector<float> getSpectral();
        
        int    getId();
        
        float  getVolumen();
        
        void changeDirX();
        void changeDirY();
        void changeDirZ();
    
        
    private:
        ci::vec3     mVel;
        ci::vec3     mPos;
        ci::vec3     mTempPos;
        ci::vec3     mPrevDir;
        ci::vec3     mDrag;
        
        ci::ColorA   mColor;
        float        mSize;
        
        int          mId;
        
        double       mTravelTime;
        
        float        mVolumen;
        std::string  mAudioName;
        cinder::DataSourceRef mAudioSource;
        
        std::vector<float>    mAudioSpectral;
        
        ci::Anim<ci::vec2>    mTranslatePos;
        
        int mTime;
        int mPrevTIme;
    };
}
