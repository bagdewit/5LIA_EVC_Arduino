#include "Motors.h"
#include <Arduino.h>
#include "definitions.cpp"
#include "Common.h"

int numSteps = 1400;
void motorLeftEncoderCount(void){
    //Serial.println("L: "+String(motorLeft._encoderVal) + "R: "+String(motorRight._encoderVal));
    motorLeft.encoderCount();
    //INFO_MOTORS("LEFT INTERRUPT");
    /*if(motorLeft._encoderVal > numSteps)
    {
      motorLeft.setMotor(0);
      QueueFlag = false;
      motorLeft._encoderVal =0;
      //Serial.println
    }*/
};

void motorRightEncoderCount(void){
    motorRight.encoderCount();
    //INFO_MOTORS("RIGHT INTERRUPT");
    //Serial.println("L: "+String(motorLeft._encoderVal) + "R: "+String(motorRight._encoderVal));
    /*if(motorRight._encoderVal > numSteps)
    {
      motorRight._encoderVal=0;
      motorRight.setMotor(0);
    }*/
};

motor::motor(int pin_PWM,int pin_EN_FWD,int pin_EN_BWD, int pin_ENC, whichMotor motorSide){
    _pin_PWM     = pin_PWM;
    _pin_EN_FWD  = pin_EN_FWD;
    _pin_EN_BWD  = pin_EN_BWD;
    _pin_ENC     = pin_ENC;
    _encoderVal  = 0;


    analogWrite(_pin_PWM, 0); 
    digitalWrite(_pin_EN_FWD, LOW);
    digitalWrite(_pin_EN_BWD, LOW);
    pinMode(_pin_PWM, OUTPUT);
    pinMode(_pin_EN_FWD, OUTPUT);
    pinMode(_pin_EN_BWD, OUTPUT);

    if(motorSide == LEFT)  // callback hack
        attachInterrupt(digitalPinToInterrupt(PIN_ENC_L),motorLeftEncoderCount,FALLING);
    if(motorSide == RIGHT) // callback hack
        attachInterrupt(digitalPinToInterrupt(PIN_ENC_R),motorRightEncoderCount,FALLING);   
    // TODO attachInterrupt(digitalPinToInterrupt(pin_ENC),std::bind(&motor::encoderCount,this),FALLING);

}


void motor::setMotor(const int ciSpeed)
{
    // 1. set the right controller config
    if (ciSpeed < 0)
    {
        digitalWrite(_pin_EN_FWD, LOW); // ensure all low
        digitalWrite(_pin_EN_BWD, LOW); // ensure all low
        digitalWrite(_pin_EN_FWD, LOW); // make low
        digitalWrite(_pin_EN_BWD, HIGH); // make backwards high
    }
    else
    {
        digitalWrite(_pin_EN_FWD, LOW); // ensure all low
        digitalWrite(_pin_EN_BWD, LOW); // ensure all low
        digitalWrite(_pin_EN_FWD, HIGH); // make forward direction high
        digitalWrite(_pin_EN_BWD, LOW); // make backward direction low
    }

    // set the desired speed
    INFO_iDRIVE("ciSpeed: "+String(ciSpeed));
    analogWrite(_pin_PWM, abs(ciSpeed));  // 0=off, 255=100% duty cycle
}


void motor::motorDemo(){
    // drive straight for 4 sec including acceleration
    for(int i=0;i<255;i=i+3)
    {
        //setMotor(PWM_L, EN_L_FWD, EN_L_BWD, i);
        //setMotor(PWM_R, EN_R_FWD, EN_R_BWD, i);   
        delay(50);
    }
    // stop the motors
    //setMotor(PIN_PWM_L, PIN_EN_L_FWD, PIN_EN_L_BWD, 0);
    //setMotor(PIN_PWM_R, PIN_EN_R_FWD, PIN_EN_R_BWD, 0);   
}

void motor::encoderCount(){
    _encoderVal++;
};


