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
    
    MainScene::MainScene(ci::ivec2  size)
    {
        
        mFboSize =  ci::vec2(size.x, size.y);
        
        //bounds
        mBounds = ci::Rectf(10, 10, mFboSize.x - 10, mFboSize.y - 10);
        mBoundColor = ci::ColorA(0.8, 0.8, 0.8, 1.0);
        
        mParticleManager =  ParticleManager::create(ci::vec3(10, 10, 0), ci::vec3(mFboSize.x - 10, mFboSize.y - 10, 0));
     
        gl::Fbo::Format format = gl::Fbo::Format();
        format.setSamples(32);
        format.setCoverageSamples(8);
        mFbo = gl::Fbo::create(size.x, size.y, format);
        
        mBkgColor = ci::ColorA(0, 0, 0.0, 0.1);
        
        mDrawBounds = true;
    }
    
    void MainScene::toggleBounds()
    {
        mDrawBounds = !mDrawBounds;
    }
    
    void MainScene::addParticle(physics::ParticleRef part)
    {
        mParticleManager->addParticle(part);
    }
    
    physics::ParticleRef MainScene::getParticle(int index)
    {
        return mParticleManager->getParticle(index);
    }
    
    void MainScene::setBkgColor(ci::ColorA mBkg){
        mBkgColor = mBkg;
        if(mBkgColor.r == 1){
            mBoundColor = ci::ColorA(0, 0, 0, 1);
        }else{
            mBoundColor = ci::ColorA(1, 1, 1, 1);
        }
    }
    
    void MainScene::createParticles()
    {
        {
            ParticleRef part = Particle::create();
            part->setPos(ci::vec3(mFboSize.x/2.0f, mFboSize.y/2.0f, 0));
        
            //time
            part->setTravelTime(120.5);
            
            //vel
            float vx = ci::randFloat(-3.5, 3.5);
            float vy = ci::randFloat(-3.5, 3.5);
            part->setVel(ci::vec3(vx, vy, 0.0));
            
            //size
            float rand =  ci::randFloat(10, 20);
            part->setSize(rand);
            
            //color
            float rg = ci::randFloat(0, 0.3);
            float rb = ci::randFloat(0, 0.3);
            ci::ColorA col = ci::ColorA(0, 0.6 + rg, 0.7 + rb, 0.7);
            part->setColor(col);
            
            //set audio name file
            part->setAudioSource(cinder::app::loadAsset("Linn Drum/LinnSnare03.wav"));
            
            mParticleManager->addParticle(part);
        }

    }
    
    void MainScene::createParticle(ci::vec3 dir, float tam, std::string name)
    {
        ParticleRef part = Particle::create();
        part->setPos(ci::vec3(mFboSize.x/2.0f, mFboSize.y/2.0f, 0));
        
        //time
        part->setTravelTime(120);
        
        //vel
        float vx = ci::randFloat(1.0, 3.5);
        float vy = ci::randFloat(1.0, 3.5);
        part->setVel(ci::vec3(vx, vy, 0.0));
        
        //size
        part->setSize(tam * TAM_MAX);
        part->setVolume(tam);
        
        //color
        float rg = ci::randFloat(0, 0.3);
        ci::ColorA col = ci::ColorA(1 - rg, 1 - rg, 1 - rg, 1.0);
        part->setColor(col);
        
        //set audio name file
        part->setAudioSource(cinder::app::loadAsset(name));
        
        mParticleManager->addParticle(part);
    }
    
    
    void MainScene::offScreenRender()
    {
        
        gl::ScopedFramebuffer scpFbo(mFbo);
        gl::ScopedColor scpColor(mBkgColor);
        gl::ScopedMatrices matrices;
        
        gl::drawSolidRect(mFbo->getBounds());
        
        gl::ScopedViewport scpVp(ivec2(0), mFbo->getSize());
        
        gl::setMatricesWindow(mFbo->getSize(), true);
        gl::setModelMatrix(ci::mat4());
        
        mParticleManager->draw(mTime);
        
        if(mDrawBounds)
        {
        
            {
                gl::ScopedColor color(mBoundColor);
                gl::drawStrokedRect(mBounds);//app::getWindowBounds());
            }
            
            drawBorders();
        }
    }
    
    void MainScene::drawBorders()
    {
        gl::ScopedColor col(mBkgColor.r, mBkgColor.g, mBkgColor.b, 1.0);
        gl::drawSolidRect(ci::Rectf(0, 0, mFbo->getSize().x, 10));
        gl::drawSolidRect(ci::Rectf(0, 0, 10, mFbo->getSize().y));
        gl::drawSolidRect(ci::Rectf(mFbo->getSize().x - 10, 0, mFbo->getSize().x, mFbo->getSize().y));
        gl::drawSolidRect(ci::Rectf(0, mFbo->getSize().y - 10, mFbo->getSize().x, mFbo->getSize().y));
    }
    
    ci::gl::Texture2dRef MainScene::getFboTexture()
    {
        return mFbo->getColorTexture();
    }
    
    
    void MainScene::setColorParticles(ci::ColorA col)
    {
        for(auto & particle : mParticleManager->getParticles()){
            particle->setColor(col);
        }
    }

    
}