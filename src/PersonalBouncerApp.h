//
//  PersonalBouncerApp.h
//  PersonalBouncer
//
//  Created by thomas on 11/20/15.
//
//

#ifndef PersonalBouncerApp_h
#define PersonalBouncerApp_h


#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

#include "MainScene.h"


class PersonalBouncerApp : public ci::app::App {
public:
    static void prepareSettings( Settings *settings );
    
    void setup() override;
    void mouseDown(  ci::app::MouseEvent event ) override;
    void update() override;
    void draw() override;
    
private:
    //Scenes Ref
    mainScene::MainSceneRef mMainScene;
    ci::vec2                mMainScenePos;
};

#endif /* PersonalBouncerApp_h */
