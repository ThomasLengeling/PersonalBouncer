//
//  ParticleManager.cpp
//  PersonalBouncer
//
//  Created by thomas on 11/19/15.
//
//

#include "ParticleManager.h"

namespace physics {
    
    using namespace ci;
    
    ParticleManager::ParticleManager(ci::vec3 sizeSpace)
    {
        auto lambert = gl::ShaderDef().lambert().color();
        gl::GlslProgRef shader = gl::getStockShader( lambert );
        mCircleBatch = gl::Batch::create( geom::Circle().subdivisions(16), shader );
        
        mDim = sizeSpace;
    }
    
    void ParticleManager::draw()
    {
        for(auto & particle : mParticleManager){
            particle->update();
            
            gl::ScopedMatrices mat;
            gl::ScopedColor col(particle->getColor());
            gl::translate(particle->getPos());
            gl::scale(ci::vec3(particle->getSize()));
            mCircleBatch->draw();
        }
        
    }
    
    void ParticleManager::update()
    {
        
    }
    
    void ParticleManager::setWindowBounds()
    {
        
    }
    
    
    void ParticleManager::addParticle(ParticleRef part)
    {
        mParticleManager.push_back(part);
    }
    
}
