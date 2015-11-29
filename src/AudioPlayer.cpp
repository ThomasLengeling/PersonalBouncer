//
//  AudioPlayer.cpp
//  PersonalBouncer
//
//  Created by thomas on 11/24/15.
//
//

#include "AudioPlayer.h"

namespace audio {
    
    
    void AudioCollection::loadAudioFile( std::string filePath)
    {
        ci::fs::path p(ci::app::getAssetPath(filePath));
        
        CI_LOG_I( "Loading Texture Sequence from " << filePath );
        
        int istep = 0; //only load a couple of images in the debug mode
        for (ci::fs::directory_iterator it(p); it != ci::fs::directory_iterator(); ++it)
        {
            
            if (ci::fs::is_regular_file(*it))
            {
                std::string fileName = it->path().filename().string();
                if( !( fileName.compare( ".DS_Store" ) == 0 ) )  //for mac?
                {
                    std::string fileN = p.string() + fileName;
                    CI_LOG_V(fileN);
                    try{
                        
                        
                        istep++;
                        
                    }
                    catch (...){
                        CI_LOG_E( "Error loading image: " << fileN );
                    }
                }
            }
        }
    }
            

    void  AudioPlayer::loadAudioFiles()
    {
        
    }

}