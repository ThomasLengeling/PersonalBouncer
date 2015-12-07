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
        
        physics::ParticleRef getParticle(int index);
        void addParticle(physics::ParticleRef part);
        
        void createParticles();
        
        void createParticle(ci::vec3 dir, float tam, std::string name);
        
        
        //bounds and size
        void toggleBounds();
        
        //offsceeen
        void offScreenRender();
        ci::gl::Texture2dRef getFboTexture();
        
        void setBkgColor(ci::ColorA mBkg);
        
        void setColorParticles(ci::ColorA col);
        
        void setTimer(float time){mTime = time;}
        
        void               drawBorders();
        
        physics::ParticleManagerRef getParticleManager(){return mParticleManager;}
        
    private:
        
        physics::ParticleManagerRef mParticleManager;
        
        ci::gl::FboRef              mFbo;
        
        ci::ivec2                   mFboSize;
        
        ci::ColorA                  mBkgColor;
        
        ci::Rectf                   mBounds;
    
        ci::ColorA                  mBoundColor;
        
        bool                        mDrawBounds;
        
        double                      mTime;
        
        ci::osc::Sender             sender;
    };
}
