//
//  Particle.hpp
//  PersonalBouncer
//
//  Created by thomas on 11/19/15.
//
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>


namespace physics {
    
    class Particle;
    typedef std::shared_ptr<Particle> ParticleRef;
    
    class Particle{
    public:
        Particle();
        
        static ParticleRef create(){return std::make_shared<Particle>();}
        
        void update();
        
        void setPos(ci::vec3 pos);
        void setVel(ci::vec3 vel);
        void setDir(ci::vec3 dir);
        void setColor(ci::ColorA col);
        void setSize(float size);
        
        ci::vec3    getPos();
        ci::vec3    getDir();
        ci::vec3    getPrevDir();
        
        ci::vec3    getVel();
        ci::ColorA  getColor();
        float       getSize();
        
        
        void changeDirX();
        void changeDirY();
        void changeDirZ();
        
    private:
        ci::vec3   mVel;
        ci::vec3   mPos;
        ci::vec3   mDir;
        ci::vec3   mPrevDir;
        ci::vec3   mDrag;
        
        ci::ColorA mColor;
        float      mSize;
    };
}

#endif /* Particle_hpp */
