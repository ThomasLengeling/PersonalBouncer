//
//  Particle.hpp
//  PersonalBouncer
//
//  Created by thomas on 11/19/15.
//
//

#pragma once

#include <stdio.h>

namespace physics {
    
    class Particle;
    typedef std::shared_ptr<Particle> ParticleRef;
    
    class Particle{
    public:
        Particle();
        
        static ParticleRef create(){return std::make_shared<Particle>();}
        
        void update();
        
        void calculateNewVel(double len);
        void calculateNewVel(ci::vec3 length);
        
        void setPos(ci::vec3 pos);
        void setVel(ci::vec3 vel);
        void setDir(ci::vec3 dir);
        void setColor(ci::ColorA col);
        void setSize(float size);
        void setAudioName(std::string name);
        void setAudioSource(cinder::DataSourceRef source);
        void setTravelTime(double time);
        void setVolume(double volumen);
        
        void setAudioSpectrall(const std::vector<float>  & mag);
        
        ci::vec3    getPos();
        ci::vec3    getDir();
        ci::vec3    getPrevDir();
        ci::vec3    getVel();
        ci::ColorA  getColor();
        float       getSize();
        std::string getAudioName();
        double      getTravelTime();
        cinder::DataSourceRef  getAudioSource();
        std::vector<float> getSpectral();
        
        float  getVolumen();
        
        void changeDirX();
        void changeDirY();
        void changeDirZ();
        
    private:
        ci::vec3     mVel;
        ci::vec3     mPos;
        ci::vec3     mDir;
        ci::vec3     mPrevDir;
        ci::vec3     mDrag;
        
        ci::ColorA   mColor;
        float        mSize;
        
        double       mTravelTime;
        
        float        mVolumen;
        std::string  mAudioName;
        cinder::DataSourceRef mAudioSource;
        
        std::vector<float>    mAudioSpectral;
    };
}
