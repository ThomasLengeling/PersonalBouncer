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
        
        mFboSize =  ci::vec2(size.x - 50, size.y - 50);
        
        //bounds
        mBounds = ci::Rectf(0, 0, mFboSize.x, mFboSize.y);
        mBoundColor = ci::ColorA(0.8, 0.8, 0.8, 1.0);
        
        mParticleManager =  ParticleManager::create(ci::vec3(mFboSize.x, mFboSize.y, 0));
     
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
    
    void MainScene::createParticles()
    {
        {
            ParticleRef part = Particle::create();
            part->setPos(ci::vec3(mFboSize.x/2.0f, mFboSize.y/2.0f, 0));
        
            //time
            part->setTravelTime(120.5);
            
            //vel
            float vx = ci::randFloat(1.0, 3.5);
            float vy = ci::randFloat(1.0, 3.5);
            part->setVel(ci::vec3(vx, vy, 0.0));
            
            //dir
            int dx = ci::randInt(-1, 1);
            int dy = ci::randInt(-1, 1);
            if(dy == 0)
                dy = -1;
            if(dx == 0)
                dx = 1;
            part->setDir(ci::vec3(dx, dy, 0));
            
            //size
            float rand =  ci::randFloat(10, 20);
            part->setSize(rand);
            
            //color
            float rg = ci::randFloat(0, 0.3);
            float rb = ci::randFloat(0, 0.3);
            ci::ColorA col = ci::ColorA(0, 0.6 + rg, 0.7 + rb, 0.7);
            part->setColor(col);
            
            //set audio name file
            //if(i == 0){
            part->setAudioSource(cinder::app::loadAsset("Linn Drum/LinnSnare03.wav"));
            
            mParticleManager->addParticle(part);
        }

    }
    
    void MainScene::createParticle(ci::vec3 dir, float tam, std::string name)
    {
        ParticleRef part = Particle::create();
        part->setPos(ci::vec3(mFboSize.x/2.0f, mFboSize.y/2.0f, 0));
        
        //time
        part->setTravelTime(120.5);
        
        //vel
        float vx = ci::randFloat(1.0, 3.5);
        float vy = ci::randFloat(1.0, 3.5);
        part->setVel(ci::vec3(vx, vy, 0.0));
        
        //dir
        part->setDir(dir);
        
        //size
        part->setSize(tam * TAM_MAX);
        part->setVolume(tam);
        
        //color
        float rg = ci::randFloat(0, 0.3);
        float rb = ci::randFloat(0, 0.3);
        ci::ColorA col = ci::ColorA(0, 0.6 + rg, 0.7 + rb, 0.7);
        part->setColor(col);
        
        //set audio name file
        part->setAudioSource(cinder::app::loadAsset(name));
        
        mParticleManager->addParticle(part);
    }
    
    
    void MainScene::offScreenRender()
    {
        
        gl::ScopedFramebuffer scpFbo(mFbo);
        
        gl::ScopedColor scpColor(mBkgColor);
        gl::drawSolidRect(mFbo->getBounds());
        
        gl::ScopedViewport scpVp(ivec2(0), mFbo->getSize());
        
        gl::ScopedMatrices matrices;
        gl::setMatricesWindow(mFbo->getSize(), true);
        gl::setModelMatrix(ci::mat4());
        
        mParticleManager->draw();
        
        if(mDrawBounds){
            gl::ScopedColor color(mBoundColor);
            gl::drawStrokedRect(mBounds);//app::getWindowBounds());
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