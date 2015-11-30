//
//  PersonalBouncerApp.h
//  PersonalBouncer
//
//  Created by thomas on 11/20/15.
//
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Log.h"

#include "MainScene.h"
#include "Commun.h"




class PersonalBouncerApp : public ci::app::App {
public:
    static void prepareSettings( Settings *settings );
    
    void setup() override;
    void mouseDown(  ci::app::MouseEvent event ) override;
    void keyUp(ci::app::KeyEvent event) override;
    void keyDown(ci::app::KeyEvent event) override;
    void update() override;
    void draw() override;
    
private:
    //Scenes Ref
    mainScene::MainSceneRef mMainScene;
    ci::vec2                mMainScenePos;
    
    
    void resetBouncer();
    
    bool        mCreateNewBall;
    bool        mDrawParticle;
    
    
    ci::vec3    mNewDir;
    float       mNewAngle;
    float       mNewTam;
};

