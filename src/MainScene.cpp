//
//  MainScene.cpp
//  PersonalBouncer
//
//  Created by thomas on 11/19/15.
//
//

#include "MainScene.h"


namespace mainScene {
    
    using namespace physics;
    using namespace ci;
    
    MainScene::MainScene(ci::vec2  size)
    {
        mParticleManager =  ParticleManager::create(size);
        
        mFboSize =  size;
        
        //bounds
        mBounds = ci::Rectf(0, 0, mFboSize.x, mFboSize.y);
        mBoundColor = ci::ColorA(0.8, 0.8, 0.8, 1.0);
     
   
        gl::Fbo::Format format = gl::Fbo::Format();
        
        mFbo = gl::Fbo::create(mFboSize.x, mFboSize.y);//, format);
        
        mBkgColor = ci::ColorA(0, 0, 0.8, 1);
        
        mDrawBounds = true;
    }
    
    void MainScene::toggleBounds()
    {
        mDrawBounds = !mDrawBounds;
    }
    
    void MainScene::createParticles()
    {
        
        ParticleRef part = Particle::create();
        part->setPos(ci::vec3(mFboSize.x/2.0f, mFboSize.y/2.0f, 0));
        part->setVel(ci::vec3(0, 0.05, 0.0));
        part->setSize(4.0f);
        mParticleManager->addParticle(part);
    }
    
    
    void MainScene::offScreenRender()
    {
        
        gl::ScopedFramebuffer scpFbo(mFbo);
        
        gl::ScopedColor scpColor(mBkgColor);
        gl::drawSolidRect(mFbo->getBounds());
        
        gl::ScopedViewport scpVp(ivec2(0), mFboSize);
        
        gl::ScopedMatrices matrices;
        gl::setMatricesWindow(mFboSize, true);
        gl::setModelMatrix(ci::mat4());
        
        mParticleManager->draw();
        
        
        if(mDrawBounds){
            gl::ScopedColor color(mBoundColor);
            gl::drawStrokedRect(mFbo->getBounds());
        }
       
    }
    
    ci::gl::Texture2dRef MainScene::getFboTexture()
    {
        return mFbo->getColorTexture();
    }
    
    void MainScene::draw()
    {
        mParticleManager->draw();
    }
    
    void MainScene::update()
    {
        mParticleManager->update();
    }
    
    
}