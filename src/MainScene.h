//
//  MainScene.hpp
//  PersonalBouncer
//
//  Created by thomas on 11/19/15.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include "cinder/gl/Fbo.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

#include "ParticleManager.h"

namespace mainScene{
    
    class MainScene;
    typedef std::shared_ptr<MainScene>  MainSceneRef;
    
    class MainScene{
    public:
        
        MainScene(ci::vec2  size);
        
        static MainSceneRef create(ci::vec2  size){
            return std::make_shared<MainScene>(size);
        }
        
        void createParticles();
        
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
        
        ci::vec2                    mFboSize;
        
        ci::ColorA                  mBkgColor;
        
        ci::Rectf                   mBounds;
    
        ci::ColorA                  mBoundColor;
        
        bool                        mDrawBounds;
    };
}


#endif /* MainScene_hpp */
