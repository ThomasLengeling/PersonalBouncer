//
//  MainScene.hpp
//  PersonalBouncer
//
//  Created by thomas on 11/19/15.
//
//
#pragma once

#include "cinder/gl/Fbo.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rand.h"

#include "ParticleManager.h"
#include "Commun.h"

namespace mainScene{
    
    class MainScene;
    typedef std::shared_ptr<MainScene>  MainSceneRef;
    
    class MainScene{
    public:
        
        MainScene(ci::ivec2  size);
        
        static MainSceneRef create(ci::ivec2  size){
            return std::make_shared<MainScene>(size);
        }
        
        void createParticles();
        
        
        void createParticle(ci::vec3 dir, float tam, std::string name);
        
        void draw();
        void update();
        
        //bounds and size
        void toggleBounds();
        
        //offsceeen
        void offScreenRender();
        ci::gl::Texture2dRef getFboTexture();
        
   
        
    private:
        
        physics::ParticleManagerRef mParticleManager;
        
        ci::gl::FboRef              mFbo;
        
        ci::ivec2                   mFboSize;
        
        ci::ColorA                  mBkgColor;
        
        ci::Rectf                   mBounds;
    
        ci::ColorA                  mBoundColor;
        
        bool                        mDrawBounds;
    };
}
