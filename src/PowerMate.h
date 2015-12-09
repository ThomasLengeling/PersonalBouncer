//
//  PowerMate.h
//  PersonalBouncer
//
//  Created by tom on 12/7/15.
//
//

#pragma once

class PowerMate;
typedef std::shared_ptr<PowerMate> PowerMateRef;

class PowerMate{
public:
    PowerMate(int maxSensi = 5){
        mTurnValue = 0;
        mPressTurnValue = 0;
        mPressTurnValue = 0;
        mSensitivity    = 0;
        mMaxSensitivity = maxSensi;
        mPress = false;
    }
    static PowerMateRef create(){return std::make_shared<PowerMate>();}
    
    void setSensitivity(int val){
        mMaxSensitivity = val;
    }
    
    int getTurnValue() {
        return mTurnValue;
    }
    
    void setTurnValue(int value) {
        mTurnValue = value;
    }
    
    int getPressTurnValue() {
        return mPressTurnValue;
    }
    
    void togglePress(bool val = true) {
        mPress = val;
    }
    
    bool isPressed() {
        return  mPress;
    }
    
    void setPressTurnValue(int press) {
        
        float diff = press  - mPrevPTurnValue;
        if (diff > 0) {
            mPressTurnValue++;
        } else if (diff < 0) {
            mPressTurnValue--;
        }
        
        mPrevPTurnValue  = press;
    }
    
    void addSensitivity(int & val){
        mSensitivity +=val;
    }
    
    void resetSensitivity(){
        mSensitivity = 0;
    }
    
    int getSensitivity(){
        return mSensitivity;
    }
    
    bool isTurnActivated(){
        bool turn = false;
        if(mSensitivity == mMaxSensitivity ){
            mSensitivity = 0;
            turn = true;
        }
        
        if(mSensitivity == mMaxSensitivity *-1){
            mSensitivity = 0;
            turn = true;
        }
        
        return turn;
        
    }
    
private:
    
    int     mTurnValue;
    int     mPressTurnValue;
    int     mPrevPTurnValue;
    
    int     mSensitivity;
    int     mMaxSensitivity;
    bool    mPress;

};