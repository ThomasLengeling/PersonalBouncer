//
//  ParticleManager.cpp
//  PersonalBouncer
//
//  Created by thomas on 11/19/15.
//
//

#include "ParticleManager.h"

namespace physics {
    
    using namespace ci;
    
    ParticleManager::ParticleManager(ci::vec3 sizeTop, ci::vec3 sizeDown)
    {
        auto lambert = gl::ShaderDef().lambert().color();
        gl::GlslProgRef shader = gl::getStockShader( lambert );
        mCircleBatch = gl::Batch::create( geom::Circle().subdivisions(32), shader );
        
        mDimTop  = sizeTop;
        mDimDown = sizeDown;
        
        CI_LOG_I(mDimDown<<" "<<mDimDown);
        
        sender.setup("127.0.0.1", 12001, false );
    }
    
    void ParticleManager::update()
    {
        
    }
    
    void ParticleManager::draw(double time)
    {
        
        for(auto & particle : mParticleManager){
            
            particle->update(time);
            vec3 pos     = particle->getPos();
            vec3 vel     = particle->getVel();
            float radius = round(particle->getSize()/2.0);
            
            {
                gl::ScopedMatrices mat;
                gl::ScopedColor col(particle->getColor());
                gl::translate(pos);
                gl::scale(ci::vec3(particle->getSize()));
                mCircleBatch->draw();
            }
            
            checkBounds(particle);
        }
    }
    
    void ParticleManager::checkBounds(ParticleRef particle)
    {
        
        vec3 pos     = particle->getPos();
        vec3 vel     = particle->getVel();
        float radius = particle->getSize()/2.0;

        
        gl::ScopedColor col(ci::ColorA(0.8, 0.3, 0.3, 0.5));
        
        //if(particle->isTransitionComplete()){
            
        
        if(pos.x > mDimDown.x - radius){
            
            particle->setPos(ci::vec3(mDimDown.x - radius, pos.y, 0));
            particle->changeDirX();
            
            //get new dir
            pos = particle->getPos();
            vel = particle->getVel();
            
    
            //float rad = atan2(pos.y, pos.x);
            //ci::vec3 dir = ci::vec3(cos(rad), sin(rad), 0);
            
            ci::vec3 newPos = pos  + (vel * ci::vec3(10000));
            ci::vec3 newPoint;
            
            ci::vec3 newPoint01 = intersect(pos, newPos, ci::vec3(mDimTop.x + radius, mDimTop.y + radius, 0), ci::vec3(mDimDown.x - radius, mDimTop.y + radius, 0));
            ci::vec3 newPoint02 = intersect(pos, newPos, ci::vec3(mDimTop.x + radius, mDimTop.y + radius, 0), ci::vec3(mDimTop.x + radius, mDimDown.y - radius, 0));
            ci::vec3 newPoint03 = intersect(pos, newPos, ci::vec3(mDimTop.x + radius, mDimDown.y - radius, 0), ci::vec3(mDimDown.x - radius, mDimDown.y - radius, 0));
            
            if(newPoint01.x != 0.0 && newPoint01.y != 0.0){
                newPoint = newPoint01;
            }else if( newPoint02.x != 0.0 && newPoint02.y != 0.0){
                newPoint = newPoint02;
            }else if( newPoint03.x != 0 && newPoint03.y != 0){
                newPoint = newPoint03;
            }
            
            gl::drawLine(pos, newPoint);
            
            gl::drawSolidCircle(ci::vec2(newPoint), 20);
            gl::drawSolidCircle(ci::vec2(pos), 20);
            
            //ci::app::console()<<"Current pos "<<pos<<std::endl;
            //ci::app::console()<<"New Point"<<newPoint<<std::endl;
            
            //vec2 distance = length(newPoint, pos);
            particle->calculateNewVel( ci::vec3(newPoint.x - pos.x, newPoint.y - pos.y, 0));
            //particle->calculateNewVel( ci::vec3(newPoint.x, newPoint.y, 0));
            
            unsigned int trackID = po::SoundManager::get()->play(particle->getAudioSource());
            po::SoundManager::get()->setGain(trackID, particle->getVolumen());
            
            osc::Message message;
            message.setAddress("/right");
            message.addIntArg(particle->getId());
            message.addIntArg(particle->getTravelTime());
            message.addIntArg(particle->getPos().x / mDimDown.x);
            sender.sendMessage(message);
            
            CI_LOG_V("RIGHT "<< particle->getTravelTime()<<" "<<particle->getPos().x / mDimDown.x);
        }
        else if(pos.x < mDimTop.x + radius){
            
            particle->setPos(ci::vec3(mDimTop.x + radius, pos.y, 0));
            particle->changeDirX();
            
            pos = particle->getPos();
            vel = particle->getVel();
            
            //float rad = atan2(pos.y, pos.x);
            //ci::vec3 dir = ci::vec3(cos(rad), sin(rad), 0);
            
            ci::vec3 newPos = pos  + (vel * ci::vec3(10000));
            ci::vec3 newPoint;
            
            ci::vec3 newPoint01 = intersect(pos, newPos, ci::vec3(mDimTop.x  + radius, mDimTop.y  + radius, 0), ci::vec3(mDimDown.x - radius, mDimTop.y  + radius, 0));
            ci::vec3 newPoint02 = intersect(pos, newPos, ci::vec3(mDimDown.x - radius, mDimTop.y  + radius, 0), ci::vec3(mDimDown.x - radius, mDimDown.y - radius, 0));
            ci::vec3 newPoint03 = intersect(pos, newPos, ci::vec3(mDimTop.x  + radius, mDimDown.y - radius, 0), ci::vec3(mDimDown.x - radius, mDimDown.y - radius, 0));
            
            
            if(newPoint01.x != 0 && newPoint01.y != 0){
                newPoint = newPoint01;
                ci::app::console()<<" p1 "<<std::endl;
            }else if( newPoint02.x != 0 && newPoint02.y != 0){
                newPoint = newPoint02;
                ci::app::console()<<" p2 "<<std::endl;
            }else if( newPoint03.x != 0 && newPoint03.y != 0){
                newPoint = newPoint03;
                ci::app::console()<<" p3 "<<std::endl;
            }
            
            gl::drawLine(pos, newPoint);
            gl::drawSolidCircle(ci::vec2(newPoint), 20);
            gl::drawSolidCircle(ci::vec2(pos), 20);
            
            //ci::app::console()<<"Current pos "<<pos<<std::endl;
            //ci::app::console()<<"New Point"<<newPoint<<std::endl;
            
            particle->calculateNewVel( ci::vec3(newPoint.x - pos.x, newPoint.y - pos.y, 0));
            //particle->calculateNewVel( ci::vec3(newPoint.x, newPoint.y, 0));
            unsigned int trackID = po::SoundManager::get()->play(particle->getAudioSource());
            po::SoundManager::get()->setGain(trackID, particle->getVolumen());
            
            osc::Message message;
            message.setAddress("/left");
            message.addIntArg(particle->getId());
            message.addFloatArg( particle->getTravelTime());
            message.addFloatArg( particle->getPos().x / mDimDown.x);
            sender.sendMessage(message);
            
            CI_LOG_V("LEFT "<< particle->getTravelTime()<<" "<<particle->getPos().x / mDimDown.x);
        }
        
        else if(pos.y > mDimDown.y - radius){
            
            particle->setPos(ci::vec3(pos.x, mDimDown.y - radius, 0));
            particle->changeDirY();
            
            pos = particle->getPos();
            vel = particle->getVel();
            
          //  float rad = atan2(pos.y, pos.x);
          //  ci::vec3 dir = ci::vec3(cos(rad), sin(rad), 0);
            
            ci::vec3 newPos = pos  + (vel * ci::vec3(10000));
            ci::vec3 newPoint;
            
            ci::vec3 newPoint01 = intersect(pos, newPos, ci::vec3(mDimTop.x  + radius, mDimTop.y + radius, 0), ci::vec3(mDimDown.x - radius, mDimTop.y  + radius, 0));
            ci::vec3 newPoint02 = intersect(pos, newPos, ci::vec3(mDimDown.x - radius, mDimTop.y + radius, 0), ci::vec3(mDimDown.x - radius, mDimDown.y - radius, 0));
            ci::vec3 newPoint03 = intersect(pos, newPos, ci::vec3(mDimTop.x  + radius, mDimTop.y + radius, 0), ci::vec3(mDimTop.x  + radius, mDimDown.y - radius, 0));
            
            if(newPoint01.x != 0 && newPoint01.y != 0){
                newPoint = newPoint01;
            }else if( newPoint02.x != 0 && newPoint02.y != 0){
                newPoint = newPoint02;
            }else if( newPoint03.x != 0 && newPoint03.y != 0){
                newPoint = newPoint03;
            }
            
            gl::drawLine(pos, newPoint);
            gl::drawSolidCircle(ci::vec2(newPoint), 20);
            gl::drawSolidCircle(ci::vec2(pos), 20);
            
            //ci::app::console()<<"Current pos "<<pos<<std::endl;
            //ci::app::console()<<"New Point"<<newPoint<<std::endl;
            
            particle->calculateNewVel( ci::vec3(newPoint.x - pos.x, newPoint.y - pos.y, 0));
            //particle->calculateNewVel( ci::vec3(newPoint.x, newPoint.y, 0));
            
            unsigned int trackID = po::SoundManager::get()->play(particle->getAudioSource());
            po::SoundManager::get()->setGain(trackID, particle->getVolumen());
            
            osc::Message message;
            message.setAddress("/top");
            message.addIntArg(particle->getId());
            message.addFloatArg( particle->getTravelTime());
            message.addFloatArg( particle->getPos().y / mDimDown.x);
            sender.sendMessage(message);
        }
       else if(pos.y < mDimTop.y + radius){
            
            particle->setPos(ci::vec3(pos.x, mDimTop.y + radius, 0));
            particle->changeDirY();
            
            pos = particle->getPos();
            vel = particle->getVel();
           
            //float rad = atan2(pos.y, pos.x);
            //ci::vec3 dir = ci::vec3(cos(rad), sin(rad), 0);
           
            ci::vec3 newPos = pos  + (vel * ci::vec3(10000));
            ci::vec3 newPoint;
           
            //ci::app::console()<<"Current pos "<<pos<<std::endl;
           
            ci::vec3 newPoint01 = intersect(pos, newPos, ci::vec3(mDimTop.x + radius, mDimTop.y   + radius, 0), ci::vec3(mDimTop.x  + radius, mDimDown.y - radius, 0));
            ci::vec3 newPoint02 = intersect(pos, newPos, ci::vec3(mDimDown.x - radius, mDimTop.y  + radius, 0), ci::vec3(mDimDown.x - radius, mDimDown.y - radius, 0));
            ci::vec3 newPoint03 = intersect(pos, newPos, ci::vec3(mDimTop.x  + radius, mDimDown.y - radius, 0), ci::vec3(mDimDown.x - radius, mDimDown.y - radius, 0));
            
            if(newPoint01.x != 0 && newPoint01.y != 0){
                newPoint = newPoint01;
            }else if( newPoint02.x != 0 && newPoint02.y != 0){
                newPoint = newPoint02;
            }else if( newPoint03.x != 0 && newPoint03.y != 0){
                newPoint = newPoint03;
            }
            
            gl::drawLine(pos, newPoint);
            gl::drawSolidCircle(ci::vec2(newPoint), 20);
            gl::drawSolidCircle(ci::vec2(pos), 20);
           
            //ci::app::console()<<"Current pos "<<pos<<std::endl;
            //ci::app::console()<<"New Point"<<newPoint<<std::endl;
           
            particle->calculateNewVel( ci::vec3(newPoint.x - pos.x, newPoint.y - pos.y, 0));
            //particle->calculateNewVel( ci::vec3(newPoint.x, newPoint.y, 0));
            unsigned int trackID = po::SoundManager::get()->play(particle->getAudioSource());
            po::SoundManager::get()->setGain(trackID, particle->getVolumen());
            
            
            osc::Message message;
            message.setAddress("/bottom");
            message.addIntArg(particle->getId());
            message.addFloatArg( particle->getTravelTime());
            message.addFloatArg( particle->getPos().y / mDimDown.x);
            sender.sendMessage(message);
        }
        
        if(pos.z > mDimDown.z - radius || pos.z < mDimTop.z){
            particle->changeDirZ();
        }
        //}
    }
    
    ci::vec3 ParticleManager::intersect(ci::vec3 point1, ci::vec3 point2, ci::vec3 point3, ci::vec3 point4){
        
        float a1, a2, b1, b2, c1, c2;
        float r1, r2 , r3, r4;
        float denom, offset, num;
        
        float x1 = point1.x, y1 = point1.y;
        float x2 = point2.x, y2 = point2.y;
        float x3 = point3.x, y3 = point3.y;
        float x4 = point4.x, y4 = point4.y;
        
        // Compute a1, b1, c1, where line joining points 1 and 2
        // is "a1 x + b1 y + c1 = 0".
        a1 = y2 - y1;
        b1 = x1 - x2;
        c1 = (x2 * y1) - (x1 * y2);
        
        // Compute r3 and r4.
        r3 = ((a1 * x3) + (b1 * y3) + c1);
        r4 = ((a1 * x4) + (b1 * y4) + c1);
        
        // Check signs of r3 and r4. If both point 3 and point 4 lie on
        // same side of line 1, the line segments do not intersect.
        if ((r3 != 0) && (r4 != 0) && sameSign(r3, r4)){
            return vec3(0);
        }
        
        // Compute a2, b2, c2
        a2 = y4 - y3;
        b2 = x3 - x4;
        c2 = (x4 * y3) - (x3 * y4);
        
        // Compute r1 and r2
        r1 = (a2 * x1) + (b2 * y1) + c2;
        r2 = (a2 * x2) + (b2 * y2) + c2;
        
        // Check signs of r1 and r2. If both point 1 and point 2 lie
        // on same side of second line segment, the line segments do
        // not intersect.
        if ((r1 != 0) && (r2 != 0) && (sameSign(r1, r2))){
            return vec3(0);
        }
        
        //Line segments intersect: compute intersection point.
        denom = (a1 * b2) - (a2 * b1);
        
        if (denom == 0) {
            return vec3(0);
        }
        
        if (denom < 0){
            offset = -denom / 2.0f;
        }
        else {
            offset = denom / 2.0f ;
        }
        
        vec3 point(0);
        // The denom/2 is to get rounding instead of truncating. It
        // is added or subtracted to the numerator, depending upon the
        // sign of the numerator.
        num = (b1 * c2) - (b2 * c1);
        if (num < 0){
            point.x = (num - offset) / denom;
        } 
        else {
            point.x = (num + offset) / denom;
        }
        
        num = (a2 * c1) - (a1 * c2);
        if (num < 0){
            point.y = ( num - offset) / denom;
        } 
        else {
            point.y = (num + offset) / denom;
        }
        
        // lines_intersect
        return point;
    }
    
    
    bool ParticleManager::sameSign(float a, float b){
        return (( a * b) >= 0);
    }
    
 
    
    void ParticleManager::setWindowBounds()
    {
        
    }
    

    void ParticleManager::calcualteInitVel(ParticleRef particle)
    {
        ci::vec3 pos    = particle->getPos();
        ci::vec3 vel    = particle->getVel();
        float    radius = particle->getSize()/2.0;
        
        ci::app::console()<<"calcuate "<<vel<<std::endl;
        
        ci::vec3 newPos = pos  + (vel * ci::vec3(10000));
        
        ci::vec3 newPoint;
        
        
        ci::vec3 newPoint01 = intersect(pos, newPos, ci::vec3(mDimTop.x + radius, mDimTop.y  + radius, 0), ci::vec3(mDimDown.x - radius, mDimTop.y  + radius, 0));
        ci::vec3 newPoint02 = intersect(pos, newPos, ci::vec3(mDimTop.x + radius, mDimTop.y  + radius, 0), ci::vec3(mDimTop.x  + radius, mDimDown.y - radius, 0));
        
        ci::vec3 newPoint03 = intersect(pos, newPos, ci::vec3(mDimTop.x + radius, mDimDown.y - radius, 0), ci::vec3(mDimDown.x - radius, mDimDown.y - radius, 0));
        ci::vec3 newPoint04 = intersect(pos, newPos, ci::vec3(mDimDown.x - radius, mDimTop.y + radius, 0), ci::vec3(mDimDown.x - radius, mDimDown.y - radius, 0));
        
        if(newPoint01.x != 0 && newPoint01.y != 0){
            newPoint = newPoint01;
        }else if( newPoint02.x != 0 && newPoint02.y != 0){
            newPoint = newPoint02;
        }else if( newPoint03.x != 0 && newPoint03.y != 0){
            newPoint = newPoint03;
        }else{
            newPoint = newPoint04;
        }
        
        gl::drawLine(pos, newPoint);
        gl::drawSolidCircle(ci::vec2(newPoint), 20);
        gl::drawSolidCircle(ci::vec2(pos), 20);
        
        particle->calculateNewVel( ci::vec3(newPoint.x - pos.x, newPoint.y - pos.y, 0));
        //particle->calculateNewVel( ci::vec3(newPoint.x, newPoint.y, 0));
    }
    
    void ParticleManager::addParticle(ParticleRef part)
    {
        part->setId( mParticleManager.size() + 1);
        mParticleManager.push_back(part);
    }
    
}
