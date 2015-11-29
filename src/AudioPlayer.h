//
//  AudioPlayer.hpp
//  PersonalBouncer
//
//  Created by thomas on 11/24/15.
//
//

#ifndef AudioPlayer_hpp
#define AudioPlayer_hpp

#include "cinder/audio/audio.h"
#include "cinder/Log.h"



namespace  audio {
    
    //Audio Collection
    class AudioCollection;
    typedef std::shared_ptr<AudioCollection> AudioCollectionRef;
    
    //Audio Player
    class AudioPlayer;
    typedef std::shared_ptr<AudioPlayer> AudioPlayerRef;
    
    
    //audio collector
    class AudioCollection{
    public:
        
        AudioCollection();
        
        static AudioCollectionRef create(){ return std::make_shared<AudioCollection>(); }
        
        void loadAudioFile(std::string filePath);
    
    private:
        
    };
    
    
    class AudioPlayer{
    public:
        
        AudioPlayer();
        static AudioPlayerRef create(){return std::make_shared<AudioPlayer>();}
        
        
        void loadAudioFiles();
        
    private:
        std::vector<AudioCollectionRef> mAudioCollections;
    };
}


#endif /* AudioPlayer_hpp */
