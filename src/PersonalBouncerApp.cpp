#include "PersonalBouncerApp.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace mainScene;



void PersonalBouncerApp::prepareSettings( Settings *settings )
{
   // settings->setHighDensityDisplayEnabled(true);
    settings->setWindowSize( 800, 800 );
    settings->setResizable(false);

}

void PersonalBouncerApp::setup()
{
    //mMainScene->createParticles();
    
    resetBouncer();
    
    mSoundCounter = 0;
    
    //true white
    //false black
    
    mBkgAlpha = 0.1;
    mBlackWhite = true;
    if(mBlackWhite){
        mBkgColor = ci::ColorA(1.0, 1.0, 1.0, mBkgAlpha);
        mNewColor = ci::ColorA(0.0, 0.0, 0.0, 1.0);
    }else{
        mBkgColor = ci::ColorA(0.0, 0.0, 0.0, mBkgAlpha);
        mNewColor = ci::ColorA(1.0, 1.0, 1.0, 1.0);
    }
    
    mMainScene = MainScene::create(getWindowSize());
    mMainScene->setBkgColor(mBkgColor);
    
    mMainScenePos   = ci::vec2(20, 20);

    mSoundNames.push_back("Performance01/LinnHat_C.wav");
    mSoundTimes.push_back(30); //sec
    
    mSoundNames.push_back("Performance01/contrabasoon_0261.mp3");
    mSoundTimes.push_back(30);
    
    mSoundNames.push_back("Performance01/contrabasoon_0312.mp3");
    mSoundTimes.push_back(50);
    
    mSoundNames.push_back("Performance01/contrabasoon_0320.mp3");
    mSoundTimes.push_back(30);
    
    mSoundNames.push_back("Performance01/Trumpet_32.mp3");
    mSoundTimes.push_back(60);
    
    mSoundNames.push_back("Performance01/violin_017.mp3");
    mSoundTimes.push_back(30);
    
    mNewPos = getWindowCenter();
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
        case '1':
            mBlackWhite = !mBlackWhite;
            if(mBlackWhite){
                mBkgColor  = ci::ColorA(1, 1, 1, mBkgAlpha);
                mMainScene->setColorParticles(ci::ColorA(0, 0, 0, 1));
            }else{
                mBkgColor  = ci::ColorA(0, 0, 0, mBkgAlpha);
                mMainScene->setColorParticles(ci::ColorA(1, 1, 1, 1));
            }
            
             mMainScene->setBkgColor(mBkgColor);
            
            break;
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
        {
            mDrawParticle = true;
            mCurrentTrackID = po::SoundManager::get()->play(loadAsset(mSoundNames[mSoundCounter]));
            po::SoundManager::get()->setGain(mCurrentTrackID, mCurrentTrackID);
            
            console()<<"DOWN PRESS DOWN"<<std::endl;
        }
            break;
        case 's': //pess long down
            console()<<"DOWN PRESS LONG DOWN"<<std::endl;
            mCreateNewBall = true;
            break;
        case 'z': //press down left
            
        {
            mDrawParticle = true;
            if(mNewTam > 0.2){
                mNewTam -= 0.1;
            }
            
            mCurrentTrackID = po::SoundManager::get()->play(loadAsset(mSoundNames[mSoundCounter]));
            po::SoundManager::get()->setGain(mCurrentTrackID, mNewTam);
            
            console()<<"PRESS DOWN LEFT"<<std::endl;
        }
            break;
        case 'x':  //press down right
        {
            mDrawParticle = true;
            if(mNewTam < 1.0){
                mNewTam += 0.1;
            }
            
            mCurrentTrackID = po::SoundManager::get()->play(loadAsset(mSoundNames[mSoundCounter]));
            po::SoundManager::get()->setGain(mCurrentTrackID, mNewTam);
            
            console()<<"PRESS DOWN RIGHT"<<std::endl;
        }
            break;
        case 'p':
            
            break;
    }
}

void PersonalBouncerApp::update()
{
    
    {
        static const double timestep = 1.0 / 30.0;
    
        // Keep track of time.
        static double time = getElapsedSeconds();
        static double accumulator = 0.0;
    
        // Calculate elapsed time since last frame.
        double elapsed = getElapsedSeconds() - time;
        time += elapsed;
        accumulator += math<double>::min( elapsed, 0.1 ); // prevents 'spiral of death'
        
        while(accumulator >= timestep ) {
            accumulator -= timestep;
            
           /// console()<< accumulator<<" "<<elapsed<<" "<<timestep<<std::endl;
            
            mMainScene->setTimer(elapsed*60);
            mMainScene->offScreenRender();
        }
    }
    
}

void PersonalBouncerApp::draw()
{
	//gl::clear( Color( 0, 0, 0 ) );
    gl::ScopedColor scpColor(mBkgColor);
    gl::drawSolidRect(getWindowBounds());
    
    ci::gl::enableAlphaBlending(true);
    
    gl::setMatricesWindow( toPixels( getWindowSize() ) );
   
    // ci::gl::disableBlending();
    // ci::gl::enableAlphaBlending(true);
    {
        gl::ScopedColor scpColor(ci::ColorA(1.0, 1.0, 1.0, 1.0));
        gl::ScopedMatrices mat;
    
       // gl::translate(mMainScenePos.x, mMainScenePos.y);
        gl::Texture2dRef tex = mMainScene->getFboTexture();
        gl::draw(tex);
    }
    
     drawParticle();
    
     createParticle();
    
}

void PersonalBouncerApp::drawParticle()
{
    if(mDrawParticle){

        ci::ColorA col;
        if(mBlackWhite){
            col = ci::ColorA(0, 0, 0, 1);
        }else{
            col  = ci::ColorA(1, 1, 1, 1);
        }
        
        gl::color(col);
        gl::drawSolidCircle(mNewPos, mNewTam * TAM_MAX, 64);
        
        float radiusOffset = mNewTam * TAM_MAX + 0.5 * TAM_MAX;
        mNewDir = vec3(cos(mNewAngle), sin(mNewAngle), 0);
        
        ci::vec2 centerDir = mNewPos + radiusOffset * vec2(mNewDir.x, mNewDir.y);
        console()<< mNewDir<<std::endl;
        
        gl::drawLine(mNewPos, centerDir);
        gl::drawStrokedCircle(mNewPos, radiusOffset);
        
        mCurrentSpectral = po::SoundManager::get()->getMagSpectrum(mCurrentTrackID);
        
        {
            if(!mCurrentSpectral.empty()){
                int bandCount = mCurrentSpectral.size();
                
                gl::ScopedMatrices mat;
                gl::translate(mNewPos);
                
                gl::ScopedColor col(0.2, 0.2, 0.2, 1.0);
                
                for (int i = 0; i < bandCount; i++) {
                    
                    float angle = lmap<float>(i, 0, bandCount, 0, M_PI * 2);
                    float lvl = mCurrentSpectral[i];
                    
                    float randIner = mNewTam * TAM_MAX*1.15;
                    //float randOuter = mNewTam * TAM_MAX*1.05 + 10*logf(lvl);
                    
                    float randOuter = mNewTam * TAM_MAX*1.15 + 1300 * logf(lvl + 1.003);
                    
                    ci::vec2 circleInit = ci::vec2(randIner * cos(angle), randIner * sin(angle));
                    ci::vec2 circleEnd = ci::vec2(randOuter * cos(angle), randOuter * sin(angle));
                    
                    gl::drawLine(circleInit, circleEnd);
                    
                }
            }
        }
    }
}

void PersonalBouncerApp::createParticle()
{
    if(mCreateNewBall){
        
        /*
        if(mNewDir.x > 0.001)
            mNewDir.x = 1.0;
        if(mNewDir.y > 0.001)
            mNewDir.y = 1.0;
        
        if(mNewDir.x < -0.001){
            console()<<mNewDir.x<<std::endl;
            mNewDir.x = -1.0;
            console()<<mNewDir.x<<std::endl;
        }
        if(mNewDir.y < -0.001)
            mNewDir.y = -1.0;
        */
        
        //float angle = atan2(pos.y - center.y, pos.x - center.x);
        //ci::vec2 dir = ci::vec2(cos(angle), sin(angle));
        
        vec2 dirPos = ci::vec2(cos(mNewAngle), sin(mNewAngle))* vec2(1) + ci::vec2(mNewPos.x, mNewPos.y);
        float angle = atan2(dirPos.y - mNewPos.y, dirPos.x - mNewPos.x);
        ci::vec2 dir = ci::vec2(cos(angle), sin(angle));
        
        console()<<"dir "<<mNewDir<<std::endl;
        
        float vx = dir.x; //cos(mNewAngle);
        float vy = dir.y; //sin(mNewAngle);
        
        console()<<"v "<<vx<<" "<<vy<<std::endl;
        
        ci::vec3 mNewVel = ci::vec3(vx, vy, 0);
        
        ci::ColorA mNewColor;
        
        if(mBlackWhite){
           mNewColor = ci::ColorA(0, 0, 0, 1);
        }else{
           mNewColor  = ci::ColorA(1, 1, 1, 1);
        }
        
        physics::ParticleRef par =  physics::Particle::create();
        
        par->setTravelTime(mSoundTimes[mSoundCounter]);
        par->setSize(mNewTam * TAM_MAX);
        par->setVolume(mNewTam);
        par->setAudioName(mSoundNames[mSoundCounter]);
        par->setAudioSource(loadAsset(mSoundNames[mSoundCounter]));
        par->setColor(mNewColor);
        par->setVel(mNewVel);
        par->setPos(vec3(mNewPos.x, mNewPos.y, 0));
        par->setAudioSpectrall(mCurrentSpectral);
        par->setCounter(mSoundTimes[mSoundCounter]);
        par->setStartPosition(vec2(mNewPos.x, mNewPos.y));
        
        mMainScene->getParticleManager()->calcualteInitVel(par);
        
        mMainScene->addParticle(par);
        
        mSoundCounter++;
        
        if(mSoundCounter >= mSoundTimes.size()){
            mSoundCounter = 0;
        }
        
        resetBouncer();
        
        CI_LOG_V(" Ball Create");
    }
}

void PersonalBouncerApp::resetBouncer()
{
    mNewTam = 0.5;
    mNewPos =  getWindowCenter();
    mNewAngle = 0;
    mNewDir   = vec3(0);
    mCreateNewBall = false;
    mDrawParticle  = false;
}

CINDER_APP( PersonalBouncerApp, RendererGl( RendererGl::Options().msaa( 32 ) ), PersonalBouncerApp::prepareSettings )

