#include "PersonalBouncerApp.h"


using namespace ci;
using namespace ci::app;
using namespace std;
using namespace mainScene;



void PersonalBouncerApp::prepareSettings( Settings *settings )
{
    //settings->setHighDensityDisplayEnabled()
    settings->setWindowSize( 1080, 720 );

}

void PersonalBouncerApp::setup()
{
    
    mMainScene = MainScene::create(getWindowSize());
    mMainScenePos   = ci::vec2(20, 20);
    
    //mMainScene->createParticles();
    
    resetBouncer();
    
}

void PersonalBouncerApp::mouseDown( MouseEvent event )
{
    
}

void PersonalBouncerApp::keyUp(KeyEvent event)
{
    switch(event.getChar()){
        case 'a':  //press down
            console()<<"UP RESS DOWN"<<std::endl;
            break;
        case 's': //pess long down
            console()<<"UP PRESS LONG DOWN"<<std::endl;
            break;
    }
}

void PersonalBouncerApp::keyDown(KeyEvent event)
{
    switch(event.getChar()){
        case 'q': //rotate left
            mDrawParticle = true;
            mNewAngle -= 0.1;
            console()<<"ROTATE LEFT"<<std::endl;
            
            break;
        case 'w': //rotate right
            mDrawParticle = true;
            mNewAngle += 0.1;
            console()<<"ROTATE RIGHT"<<std::endl;
           
            break;
        case 'a':  //press down
        
            console()<<"DOWN PRESS DOWN"<<std::endl;
            break;
        case 's': //pess long down
            console()<<"DOWN PRESS LONG DOWN"<<std::endl;
            mCreateNewBall = true;
            break;
        case 'z': //press down left
            if(mNewTam > 0.2){
                mNewTam -= 0.1;
            }
            
            console()<<"PRESS DOWN LEFT"<<std::endl;
            break;
        case 'x':  //press down right
            if(mNewTam < 1.0){
                mNewTam += 0.1;
            }
            
            console()<<"PRESS DOWN RIGHT"<<std::endl;
            break;
        case 'p':
            
            break;
    }
}

void PersonalBouncerApp::update()
{
    mMainScene->offScreenRender();
    
    if(mCreateNewBall){
        
        if(mNewDir.x > 0.01)
           mNewDir.x = 1.0;
        if(mNewDir.y > 0.01)
            mNewDir.y = 1.0;
        
        if(mNewDir.x < -0.01){
            console()<<mNewDir.x<<std::endl;
            mNewDir.x = -1.0;
             console()<<mNewDir.x<<std::endl;
        }
        if(mNewDir.y < -0.01)
            mNewDir.y = -1.0;
        
        mMainScene->createParticle(mNewDir, mNewTam, "Linn Drum/LinnSnare01.wav");
        resetBouncer();
        CI_LOG_V(" Ball Create");
    }
    
}

void PersonalBouncerApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    ci::gl::enableAlphaBlending(true);
    ci::gl::enableAlphaBlendingPremult();
    
    gl::setMatricesWindow( toPixels( getWindowSize() ) );
    
    if(mDrawParticle){
        
        gl::color(ci::ColorA(1.0, 1.0, 1.0, 0.5));
        ci::vec2 center = getWindowCenter();
        
        gl::drawSolidCircle(center, mNewTam * TAM_MAX, 64);
        
    
        float radiusOffset = mNewTam * TAM_MAX + 0.2 * TAM_MAX;
        mNewDir = vec3(cos(mNewAngle), sin(mNewAngle), 0);
        
        ci::vec2 centerDir = getWindowCenter() + radiusOffset * vec2(mNewDir.x, mNewDir.y);
        console()<< mNewDir<<std::endl;
        
        gl::color(ci::ColorA(1.0, 1.0, 1.0, 0.8));
        gl::drawLine(center, centerDir);
        
        gl::color(ci::ColorA(1.0, 1.0, 1.0, 1.0));
        gl::drawStrokedCircle(center, radiusOffset);
        
    }
    
    ci::gl::disableBlending();
     ci::gl::enableAlphaBlending(true);
    {
        gl::ScopedMatrices mat;
    
        gl::translate(mMainScenePos.x, mMainScenePos.y);
        gl::Texture2dRef tex = mMainScene->getFboTexture();
        gl::draw(tex);
    }
    
}

void PersonalBouncerApp::resetBouncer()
{
    mNewTam = 0.5;
    
    mNewAngle = 0;
    mNewDir   = vec3(0);
    mCreateNewBall = false;
    mDrawParticle  = false;
}

CINDER_APP( PersonalBouncerApp, RendererGl( RendererGl::Options().msaa( 32 ) ), PersonalBouncerApp::prepareSettings )

