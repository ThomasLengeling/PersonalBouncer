//
//  ParticleManager.hpp
//  PersonalBouncer
//
//  Created by thomas on 11/19/15.
//
//

#ifndef ParticleManager_hpp
#define ParticleManager_hpp

#include "cinder/gl/Batch.h"
#include "cinder/gl/gl.h"

#include "Particle.h"

namespace physics {
    
    class ParticleManager;
    typedef std::shared_ptr<ParticleManager> ParticleManagerRef;
    
    class ParticleManager{
    public:
        
        ParticleManager(ci::vec3 sizeSpace);
        
        static ParticleManagerRef create(ci::vec3 sizeSpace){
            return std::make_shared<ParticleManager>(sizeSpace);
        }
        
        void draw();
        void update();
        
        void setWindowBounds();
        
        void addParticle(ParticleRef part);
        
        
        ci::vec3 intersect(ci::vec3 point1, ci::vec3 point2, ci::vec3 point3, ci::vec3 point4);
        
        bool sameSign(float a, float b);
        
    private:
        
        std::vector<ParticleRef> mParticleManager;
        
        ci::gl::BatchRef         mCircleBatch;
        
        ci::vec3                 mDim;
        
    };
}


#endif /* ParticleManager_hpp */
