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
#include "cinder/gl/Batch.h"

#include "MainScene.h"
#include "Commun.h"

#include "PowerMate.h"

#include "OscListener.h"

#include "poSoundManager/poSoundManager.h"


class PersonalBouncerApp : public ci::app::App {
public:
    static void prepareSettings( Settings *settings );
    
    void setup() override;
    void mouseDown(  ci::app::MouseEvent event ) override;
    void keyUp(ci::app::KeyEvent event) override;
    void keyDown(ci::app::KeyEvent event) override;
    void update() override;
    void draw() override;
    void cleanup() override;
    
private:
    //Scenes Ref
    mainScene::MainSceneRef mMainScene;
    ci::vec2                mMainScenePos;
    
    
    void resetBouncer();
    void createParticle();
    void drawParticle();
    
    //Load Audios
    void setupAudios();
    int  getNumberOfAudios( std::string filePath, ci::ColorA startCol, ci::ColorA endCol, std::vector<std::string> & vectorNames, std::vector<ci::ColorA> & colors);
   
    
    int mCurrentSoundLib;
    
    struct AudioFiles{
        int mIndex;
        int currentIndex;
        ci::ColorA mColor;
        std::vector<std::string> mFiles;
        std::vector<ci::ColorA>  mColors;
        std::string mParent;
    };
    
    std::vector<AudioFiles> mAudioFiles;
    
    //Current Audio File
    std::string mCurrentAudioFile;
    ci::ColorA  mCurrentColor;
    
    //OSC
    void oscListener();
    void setupOSC();
    ci::osc::Listener          mListener;
    ci::osc::Sender            mSender;
    
    bool               mCreateNewBall;
    bool               mDrawParticle;
    
    std::vector<float> mCurrentSpectral;
    unsigned int       mCurrentTrackID;
    ci::vec3           mNewDir;
    float              mNewAngle;
    float              mNewTam;
    ci::vec2           mNewPos;
    ci::ColorA         mNewColor;
    bool               mVolumenChanged;
    
    int                mTimeCounter;
    
    //ARC
    void               drawArc(float x, float y, float deg, float rad, float w, float trans);
    float            * sinLUT;
    float            * cosLUT;
    float              SINCOS_PRECISION;
    int                SINCOS_LENGTH;
    
    //Colors
    bool               mBlackWhite;
    ci::ColorA         mBkgColor;
    float              mBkgAlpha;
    
    
    //Power Mate
    void setupPowerMate();
    std::vector<PowerMateRef> mPowerMates;
    int mPMThreshold;
    
    
    //pick the sound and times
    int                      mSoundCounter;
    std::vector<std::string> mSoundNames;
    std::vector<int>         mSoundTimes;
};

