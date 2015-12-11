//
//  ParticleManager.hpp
//  PersonalBouncer
//
//  Created by thomas on 11/19/15.
//
//

#pragma once

#include "cinder/gl/Batch.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include "poSoundManager/poSoundManager.h"
#include "SoundManager.h"

#include "Commun.h"

#include "OscSender.h"

#include "Particle.h"


#define  SURROUND 0


#ifndef SURROUND 1
    const int leftChannel = 4;
    const int downChannel = 3;
    const int rightChannel = 8;
    const int upChannel = 6;
#else
    const int leftChannel = 0;
    const int downChannel = 0;
    const int rightChannel = 0;
    const int upChannel = 0;
#endif

namespace physics {
    
    class ParticleManager;
    typedef std::shared_ptr<ParticleManager> ParticleManagerRef;
    
    class ParticleManager{
    public:
        
        ParticleManager(ci::vec3 sizeTop, ci::vec3 sizeSpace);
        
        static ParticleManagerRef create(ci::vec3 sizeTop, ci::vec3 sizeSpace){
            return std::make_shared<ParticleManager>(sizeTop, sizeSpace);
        }
        
        void draw(double time);
        void update();
        
        void checkBounds(ParticleRef particle);
        
        void setWindowBounds();
        
        void addParticle(ParticleRef part);
        
        
        ci::vec3 intersect(ci::vec3 point1, ci::vec3 point2, ci::vec3 point3, ci::vec3 point4);
        
        bool sameSign(float a, float b);
        
        ParticleRef getParticle(int index){return mParticleManager[index];}
        
        std::vector<ParticleRef> getParticles(){return mParticleManager;}
        
        void calcualteInitVel(ParticleRef particle);
        
        void clean(){mParticleManager.clear();}
        
    private:
        
        std::vector<ParticleRef> mParticleManager;
        
        ci::gl::BatchRef         mCircleBatch;
        
        ci::vec3                 mDimTop;
        ci::vec3                 mDimDown;
    
    };
}
