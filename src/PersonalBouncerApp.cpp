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
    
    setupOSC();
    
    resetBouncer();
    
    setupPowerMate();
    
    mSoundCounter = 0;
    
    mVolumenChanged = false;
    
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
    
    setupAudios();
    
    mNewPos = getWindowCenter();
    
    mTimeCounter = COUNT_DEFAULT;
    
    
    float DEG_TO_RAD = 	0.01745329238474369f;
    
    //SETUP ARC
    SINCOS_PRECISION = 1.0;
    SINCOS_LENGTH    = int((360.0/SINCOS_PRECISION));
    
    // Fill the tables
    sinLUT = new float[SINCOS_LENGTH];
    cosLUT = new float[SINCOS_LENGTH];
    
    for (int i = 0; i < SINCOS_LENGTH; i++) {
        sinLUT[i]= (float)sin(i * DEG_TO_RAD * SINCOS_PRECISION);
        cosLUT[i]= (float)cos(i * DEG_TO_RAD * SINCOS_PRECISION);
    }
    
}

void PersonalBouncerApp::setupPowerMate()
{
    //OSC power Mate
    for(int i = 0; i < 3; i++){
        mPowerMates.push_back( PowerMate::create());
    }
    
    mPMThreshold = 5;
}

void PersonalBouncerApp::setupAudios()
{
    std::vector<std::string>  mAudioFolder;
    
    std::vector<ci::ColorA>   mStartColors;
    std::vector<ci::ColorA>   mEndColors;
    
    mAudioFolder.push_back("BASS");
    mStartColors.push_back(ci::ColorA(0, 0, 0.2, 1));
    mEndColors.push_back(ci::ColorA(0, 0, 1, 1));
    
    mAudioFolder.push_back("DRUM KITS"); //rojas
    mStartColors.push_back(ci::ColorA(0.2, 0, 0, 1));
    mEndColors.push_back(ci::ColorA(1, 0, 0, 1));
    
    mAudioFolder.push_back("LEAD"); //amarrillos
    mStartColors.push_back(ci::ColorA(0.3, 0.3, 0, 1));
    mEndColors.push_back(ci::ColorA(1, 1, 0, 1));
    
    mAudioFolder.push_back("PAD"); //aqua
    mStartColors.push_back(ci::ColorA(0, 0.3, 0.3, 1));
    mEndColors.push_back(ci::ColorA(0, 1, 1, 1));
    
    int i = 0;
    for(auto & name : mAudioFolder){
        AudioFiles mAF;
        int num = getNumberOfAudios(name, mStartColors.at(i), mEndColors.at(i), mAF.mFiles, mAF.mColors);
        console()<<num<<std::endl;
        
        mAF.mParent = name;
        mAF.mColor = mEndColors.at(i);
        mAudioFiles.push_back(mAF);
        i++;
    }
    
    //test read files
    for(auto & mFiles : mAudioFiles){
         CI_LOG_V("parent "<<mFiles.mParent);
        for(auto & names : mFiles.mFiles){
            CI_LOG_V("names "<<names);
        }
        
        for(auto & colors : mFiles.mColors){
            CI_LOG_V("colors "<<colors);
        }
    }
    
    mCurrentSoundLib = 0;
    
    std::string mFileParent = mAudioFiles.at(0).mParent;
    std::string mFileName =  mAudioFiles.at(0).mFiles.at(2);
    mCurrentAudioFile = mFileParent+"/"+mFileName;
    mCurrentColor =  mAudioFiles.at(0).mColor;
}

int  PersonalBouncerApp::getNumberOfAudios( std::string filePath, ci::ColorA startCol, ci::ColorA endCol, std::vector<std::string> & vectorNames, std::vector<ci::ColorA> & colors)
{
    
    int mSize = 0;
    ci::fs::path pNum(ci::app::getAssetPath(filePath));
    
    for (ci::fs::directory_iterator it(pNum); it != ci::fs::directory_iterator(); ++it)
    {
        if (ci::fs::is_regular_file(*it))
        {
            std::string fileName = it->path().filename().string();
            if( !( fileName.compare( ".DS_Store" ) == 0 ) )  //for mac?
            {
                mSize++;
            }
        }
    }
    
    
    ci::fs::path p(ci::app::getAssetPath(filePath));
    
    int istep = 0; //only load a couple of images in the debug mode

    for (ci::fs::directory_iterator it(p); it != ci::fs::directory_iterator(); ++it)
    {
        if (ci::fs::is_regular_file(*it))
        {
            std::string fileName = it->path().filename().string();
            if( !( fileName.compare( ".DS_Store" ) == 0 ) )  //for mac?
            {
                std::string fileN = p.string() + fileName;
                //CI_LOG_V(fileName);
                vectorNames.push_back(fileName);
                
                float currentSize = (float)istep/(float)mSize;
                float mapR = lmap<float>(currentSize, 0.0, 1.0, startCol.r, endCol.r);
                float mapG = lmap<float>(currentSize, 0.0, 1.0, startCol.g, endCol.g);
                float mapB = lmap<float>(currentSize, 0.0, 1.0, startCol.b, endCol.b);
                
                ci::ColorA col = ci::ColorA(mapR, mapG, mapB, 1.0);
                colors.push_back(col);
                try{
                    istep++;
                    
                }
                catch (...){
                    CI_LOG_E( "Error loading image: " << fileN );
                }
            }
        }
    }
    
    CI_LOG_I( "Number of Sequence from " << filePath <<" "<<istep);
    return istep;
}

void PersonalBouncerApp::setupOSC()
{
    console()<<"setup OSC"<<std::endl;
    
    try{
        mListener.setup( 13210 );
    }catch(std::exception & e){
        console()<<e.what()<<std::endl;
    }
    
    mSender.setup("127.0.0.1", 12110, true );
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
        case '2':
            mTimeCounter--;
            if(mTimeCounter < COUNT_MIN){
                mTimeCounter = COUNT_MIN;
            }
            console()<<"count "<<mTimeCounter<<std::endl;
            break;
        case '3':
            mTimeCounter++;
            if(mTimeCounter > COUNT_MAX){
                mTimeCounter = COUNT_MAX;
            }
            console()<<"count "<<mTimeCounter<<std::endl;
            break;
        case '4':
            mBkgAlpha = 0.0;
            break;
        case '5':
            mBkgAlpha = 1.0;
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
            mCurrentTrackID = po::SoundManager::get()->play(loadAsset(mCurrentAudioFile), 1);
            po::SoundManager::get()->setGain(mCurrentTrackID, 1.0);
            
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
            
            mCurrentTrackID = po::SoundManager::get()->play(loadAsset(mCurrentAudioFile), 1);
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
            
            mCurrentTrackID = po::SoundManager::get()->play(loadAsset(mCurrentAudioFile), 1);
            po::SoundManager::get()->setGain(mCurrentTrackID, mNewTam);
            
            console()<<"PRESS DOWN RIGHT"<<std::endl;
        }
            break;
        case 'p':
        {
            osc::Message message;
            message.setAddress("/brightness");
            message.addFloatArg(0);
            mSender.sendMessage(message);
        }
            break;
        case 'l':
        {
            osc::Message message;
            message.setAddress("/brightness");
            message.addFloatArg(255);
            mSender.sendMessage(message);
        }
            break;
    }
}

void PersonalBouncerApp::update()
{
    oscListener();
    
    po::SoundManager::get()->update();
    
    if(mVolumenChanged){
        if(getElapsedFrames() % 20 == 0){
            osc::Message message;
            message.setAddress("/brightness");
            message.addFloatArg( int(mNewTam * 255));
            mSender.sendMessage(message);
            mVolumenChanged = false;
        }
    }
    
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
            col = mCurrentColor;//ci::ColorA(0, 0, 0, 1);
        }else{
            col  = ci::ColorA(1, 1, 1, 1);
        }
        
        gl::color(col);
        gl::drawSolidCircle(mNewPos, mNewTam * TAM_MAX, 64);
        
        float radiusOffset = mNewTam * TAM_MAX + 0.7 * TAM_MAX;
        mNewDir = vec3(cos(mNewAngle), sin(mNewAngle), 0);
        
        ci::vec2 centerDir = mNewPos + vec2(radiusOffset + 0.3 * TAM_MAX) * vec2(mNewDir.x, mNewDir.y);
        
        gl::drawLine(mNewPos, centerDir);
        gl::drawStrokedCircle(mNewPos, radiusOffset);
        
    
        //mTimeCounter
        {
            //(float x,float y,float deg,float rad,float w)
            gl::ScopedColor col(ci::ColorA(0, 0, 0, 0.4));
          

            gl::ScopedMatrices mat;
            gl::translate(mNewPos);
            gl::rotate((mNewAngle));
            
            float rad = lmap<float>(mTimeCounter, COUNT_MIN, COUNT_MAX, 30, 360);
            
            //drawArc(mNewPos.x, mNewPos.y, rad, mNewTam * TAM_MAX  + 0.25 * TAM_MAX, 10, mNewAngle);
            drawArc(0, 0, rad, mNewTam * TAM_MAX  + 0.25 * TAM_MAX, 11, mNewAngle);
        }
        
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
                    
                    ci::vec2 circleInit = ci::vec2(randIner  * cos(angle + mNewAngle), randIner  * sin(angle + mNewAngle));// + ci::vec2(mNewDir.x, mNewDir.y);
                    ci::vec2 circleEnd  = ci::vec2(randOuter * cos(angle + mNewAngle), randOuter * sin(angle + mNewAngle));
                    
                    gl::drawLine(circleInit, circleEnd);
                    
                }
            }
        }
    }
}

void PersonalBouncerApp::createParticle()
{
    if(mCreateNewBall){
        
        vec2 dirPos = ci::vec2(cos(mNewAngle), sin(mNewAngle))* vec2(1) + ci::vec2(mNewPos.x, mNewPos.y);
        float angle = atan2(dirPos.y - mNewPos.y, dirPos.x - mNewPos.x);
        ci::vec2 dir = ci::vec2(cos(angle), sin(angle));
        
        float vx = dir.x; //cos(mNewAngle);
        float vy = dir.y; //sin(mNewAngle);
    
        ci::vec3 mNewVel = ci::vec3(vx, vy, 0);
        ci::ColorA mNewColor;
        
        if(mBlackWhite){
            mNewColor = mCurrentColor;//ci::ColorA(0, 0, 0, 1);
        }else{
           mNewColor  = ci::ColorA(1, 1, 1, 1);
        }
        
        physics::ParticleRef par =  physics::Particle::create();
        
        par->setTravelTime(mTimeCounter);//mSoundTimes[mSoundCounter]);
        par->setSize(mNewTam * TAM_MAX);
        par->setVolume(mNewTam);
        par->setAudioName(mCurrentAudioFile);
        par->setAudioSource(loadAsset(mCurrentAudioFile));
        par->setColor(mNewColor);
        par->setVel(mNewVel);
        par->setPos(vec3(mNewPos.x, mNewPos.y, 0));
        par->setAudioSpectrall(mCurrentSpectral);
        par->setCounter(mTimeCounter);//mSoundTimes[mSoundCounter]);
        par->setStartPosition(vec2(mNewPos.x, mNewPos.y));
        
        mMainScene->getParticleManager()->calcualteInitVel(par);
        
        mMainScene->addParticle(par);
        
        resetBouncer();
        
        CI_LOG_V(" Ball Create");
    }
}

void PersonalBouncerApp::oscListener()
{
    while (mListener.hasWaitingMessages()) {
        ci::osc::Message message;
        mListener.getNextMessage(&message);
        
       // ci::app::console()<<"msg got "<<message.getAddress()<<" "<<message.getNumArgs()<<" "<<message.getArgTypeName(0)<<" "<<message.getArgTypeName(1)<<std::endl;
        if (message.getAddress() == "/pmWheelTurn"){
            
            try {
                int  index = message.getArgAsInt32(0);
                int  turnValue  = message.getArgAsInt32(1);
                int  prevTurnValue;
                int  prevPressValue;
                PowerMateRef mPM = mPowerMates.at(index);
                
                if(mPM->isPressed()){
                    prevPressValue = mPM->getPressTurnValue();
                    mPM->setPressTurnValue(turnValue);
                }else{
                    prevTurnValue = mPM->getTurnValue();
                    mPM->setTurnValue(turnValue);
                }
                
                //Sounds
                if(index == 0 ){
                    if(mPM->isPressed()){
                        int diffPress = mPM->getPressTurnValue() - prevPressValue;
                        console()<<mPM->getPressTurnValue() - prevPressValue<<" "<<mPM->getPressTurnValue()<<" "<<prevPressValue<<std::endl;
                        
                        if( diffPress == 1 || diffPress == -1){
                            
                            mPM->addSensitivity(diffPress);
                            if(mPM->isTurnActivated()){
                            
                                mCurrentSoundLib += diffPress;
                                
                                if( mCurrentSoundLib < 0){
                                    mCurrentSoundLib = mAudioFiles.size() - 1;
                                }
                        
                                if(mCurrentSoundLib >= mAudioFiles.size()){
                                    mCurrentSoundLib = 0;
                                }
                                
                                mCurrentColor = mAudioFiles.at(mCurrentSoundLib).mColor;
                                
                                std::string mFileParent = mAudioFiles.at(mCurrentSoundLib).mParent;
                                
                                console()<<"Parent "<< mFileParent<<" "<<mCurrentSoundLib<<std::endl;
                            }
                        }
                    }else{
                        int diff = mPM->getTurnValue() - prevTurnValue;
                        console()<<" diff "<<diff<<std::endl;
                        if( diff == 1 || diff == -1){
                        
                            mPM->addSensitivity(diff);
                            console()<<"sen: "<<mPM->getSensitivity()<<std::endl;
                            
                            if(mPM->isTurnActivated()){
                                console()<< mCurrentSoundLib<<" - "<<mAudioFiles.size()<<" "<<mSoundCounter<<" - "<<mAudioFiles.at(mCurrentSoundLib).mFiles.size()<< std::endl;
                                std::string mFileParent = mAudioFiles.at(mCurrentSoundLib).mParent;
                                std::string mFileName =  mAudioFiles.at(mCurrentSoundLib).mFiles.at(mSoundCounter);
    
                                mCurrentAudioFile = mFileParent+"/"+mFileName;
                                mCurrentTrackID = po::SoundManager::get()->play(loadAsset(mCurrentAudioFile), 1);
                                po::SoundManager::get()->setGain(mCurrentTrackID, 1.0);
                                
                                mCurrentColor = mAudioFiles.at(mCurrentSoundLib).mColors.at(mSoundCounter);
                                
                                mDrawParticle = true;
                
                                mSoundCounter += diff;
                                
                                console()<<"files "<<mFileParent<<" "<<mSoundCounter<<std::endl;
                                
                                int maxFiles = mAudioFiles.at(mCurrentSoundLib).mFiles.size();
                                if(mSoundCounter >= maxFiles){
                                    mSoundCounter = 0;
                                }
                                
                                if(mSoundCounter < 0){
                                    mSoundCounter =  maxFiles - 1;
                                }
                            }
                        }
                    }
                    
                // volumen
                }else if( index  == 1){
                    if(mPM->isPressed()){
                        int diffPress = mPM->getPressTurnValue() - prevPressValue;
                        
                        if( diffPress == 1 || diffPress == -1){
                            
                            mPM->addSensitivity(diffPress);
                            if(mPM->isTurnActivated()){
                                mNewTam += diffPress * 0.1;
                                
                                if(mNewTam > 1.0){
                                    mNewTam = 1.0;
                                }
                                
                                if(mNewTam < 0.0){
                                    mNewTam = 0.0;
                                }
                                
                                mCurrentTrackID = po::SoundManager::get()->play(loadAsset(mCurrentAudioFile), 1);
                                po::SoundManager::get()->setGain(mCurrentTrackID, mNewTam);
                                
                                mDrawParticle = true;
                                mVolumenChanged = true;
                                
                                console()<<"new Volume "<<mNewTam<<std::endl;
                            }
                    
                        }
                    }else{
                        int diff = mPM->getTurnValue() - prevTurnValue;
                        if( diff == 1 || diff == -1){
                            
                            mNewAngle += diff * 0.1;
                        }
                        mDrawParticle = true;
                    }
                    
                }
                else if( index == 2){
                    mDrawParticle = true;
                    if(mPM->isPressed()){
                        
                    }else{
                        int diff = mPM->getTurnValue() - prevTurnValue;
                        if( diff == 1 || diff == -1){
                            mTimeCounter += diff;
                            
                            if(mTimeCounter < COUNT_MIN){
                                mTimeCounter = COUNT_MIN;
                            }
                        
                  
                            if(mTimeCounter > COUNT_MAX){
                                mTimeCounter = COUNT_MAX;
                            }
                            
                        }
                        mDrawParticle = true;
                    }
                }
            }
            catch (...) {
                ci::app::console() << "Exception reading argument as float "<< std::endl;
            }
        }
        
        if(message.getAddress() == "/pmButtonDown"){
            
            try {
                int  index = message.getArgAsInt32(0);
                mPowerMates.at(index)->togglePress(true);
                mPowerMates.at(index)->resetSensitivity();
                console()<<" toggle Down "<<index<<std::endl;
                
            }
            catch (...) {
                ci::app::console() << "Exception reading argument as float" << std::endl;
            }
        }
        
        if(message.getAddress() == "/pmButtonUp"){
            
            try {
                int  index = message.getArgAsInt32(0);
                
                if(mPowerMates.at(index)->isPressed()){
                    if(index == 2){
                        mCreateNewBall = true;
                        console()<<"create ball"<<std::endl;
                    }
                    
                    if(index == 1){
                       // mPowerMates.at(index)->setSensitivity(15);
                    }
                    
                    if(index  == 0){
                        if(mSoundCounter >= mAudioFiles.at(mCurrentSoundLib).mFiles.size()){
                            mSoundCounter = mAudioFiles.at(mCurrentSoundLib).mFiles.size() - 1;
                        }
                    }
                }
                
                mPowerMates.at(index)->togglePress(false);
                mPowerMates.at(index)->resetSensitivity();
                console()<<" toggle Up "<<index<<std::endl;
            
            }
            catch (...) {
                ci::app::console() << "Exception reading argument as float" << std::endl;
            }
        }
    }
}

void PersonalBouncerApp::resetBouncer()
{
    mNewTam = 0.5;
    mNewPos =  getWindowCenter();
    mNewAngle = 0;
    mTimeCounter = COUNT_DEFAULT;
    mNewDir   = vec3(0);
    mCreateNewBall = false;
    mDrawParticle  = false;
}

void PersonalBouncerApp::drawArc(float x,float y,float deg,float rad, float w, float trans)
{
    int a = int( min<float>(deg/SINCOS_PRECISION, SINCOS_LENGTH-1));
    
    gl::VertBatch vert(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= a; i++) {
        vert.vertex(cosLUT[i]*(rad + trans) + x, sinLUT[i]*(rad + trans) + y);
        vert.vertex(cosLUT[i]*(rad + trans + w) + x, sinLUT[i]*(rad + trans + w) + y);
    }
    vert.draw();
}

void PersonalBouncerApp::cleanup()
{
    delete cosLUT;
    delete sinLUT;
}

CINDER_APP( PersonalBouncerApp, RendererGl( RendererGl::Options().msaa( 32 ) ), PersonalBouncerApp::prepareSettings )

