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
    
    mMainScene = MainScene::create(ci::vec2(640, 640));
    mMainScenePos   = ci::vec2(20, 20);
    
    mMainScene->createParticles();
}

void PersonalBouncerApp::mouseDown( MouseEvent event )
{
    
}

void PersonalBouncerApp::update()
{
    mMainScene->offScreenRender();
}

void PersonalBouncerApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    ci::gl::enableAlphaBlending(true);
    ci::gl::enableAlphaBlendingPremult();
    
    {
        gl::ScopedMatrices mat;
    
        gl::translate(mMainScenePos.x, mMainScenePos.y);
        gl::Texture2dRef tex = mMainScene->getFboTexture();
        gl::draw(tex);
    }
}

CINDER_APP( PersonalBouncerApp, RendererGl( RendererGl::Options().msaa( 16 ) ), PersonalBouncerApp::prepareSettings )

