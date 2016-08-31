#include "Idrive.h"
#include "definitions.cpp"
#include "Instruction.h"
#include "timer.h"
#include "Common.h"
#include <stdarg.h>
#include "Instruction.h"
#include "solar.h"

void p(char *fmt, ... ){
        char buf[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 128, fmt, args);
        va_end (args);
        Serial.print(buf);
}

iDrive * iDrivep; // used for callback fix


void callbackCheckStepsReached(void){
    //p("going to call adress: %x \n", iDrivep);
    iDrivep->checkStepsReached();
    
};

int iDrive::obtainStepsLeft(char *iString) {
    int sign = (iString[4]== '-')?-1:1;
    return sign*(_3chars2dec(&iString[5]));
};

int iDrive::obtainStepsRight(char *iString) {
     int sign = (iString[8]== '-')?-1:1;
    return sign*(_3chars2dec(&iString[9]));
};

int iDrive::obtainDuration(char *iString) {
    return _4chars2dec(&iString[12]);
};

iDrive::iDrive(char * iString) {
    test = 5;
    // format: |ID|INSTR_TYPE-3|dirLeft-1|speedLeft-3|dirRight-1|speedRight-3|durationms-4
    INFO_iDRIVE("iDrive object created by idrive constructor");

    // obtain the instruction parameters
    _instrType = DRI;
    _id = obtainId(iString);
    _stepsLeft = obtainStepsLeft(iString);
    _stepsRight = obtainStepsRight(iString);
    
    _stepsLeft = _stepsLeft/MOTORLEFTOFFSET;
    _stepsRight = _stepsRight/MOTORRIGHTOFFSET;
    
    _duration = obtainDuration(iString);

    INFO_iDRIVE("id:"+String(_id)+" stepsLeft:"+String(_stepsLeft)+" stepsRight:"+String(_stepsRight)+" duration:"+String(_duration));
};

void iDrive::execute() {
    INFO_iDRIVE("idrive instruction execute!"+String(_stepsLeft) + "right: "+String(_stepsRight));
    INFO_iDRIVE("SET MOTORS");
    
    motorLeft._encoderVal =0;
    motorRight._encoderVal =0;
    //motorLeft.setMotor(0);
    //motorRight.setMotor(0);
    if(_stepsLeft !=0){
      motorLeft.setMotor(SIGN(_stepsLeft)* MOTORSPEED);
      INFO_iDRIVE("triggered left");}
    //else
      //motorLeft.setMotor(0);
    
    if(_stepsRight !=0){
      motorRight.setMotor(SIGN(_stepsRight)*MOTORSPEED);
      INFO_iDRIVE("triggered right");}
    //else
      //motorRight.setMotor(0);
    
    // REGISTER REACHED CHECK:
    iDrivep = this;
    //p("%x, p: %x", this,iDrivep);
    
    _checkStepsReachedId = t.every(1, callbackCheckStepsReached) ;
};

void iDrive::checkStepsReached(void){
  test++;
  //INFO_iDRIVE("TEST:"+String(test));
  bool motorLeftReached = false;
  bool motorRightReached = false;
  
  INFO_iDRIVE("CHECK TICKERS L:"+String(motorLeft._encoderVal)+" | R: "+String(motorRight._encoderVal) + "StepsLeft: "+String((int)_stepsLeft));
  //p("objADDR-> %x testADDR: %x testVAL: %i \n", this,&test, test);
  if(!motorLeftReached && ((int)motorLeft._encoderVal >= abs((int)_stepsLeft)))
    {
      INFO_iDRIVE("LEFT STOP");

      //motorLeft.setMotor(-1*SIGN(_stepsLeft)*255); // FORCE STOP MOTOR
      //delay(1);
      digitalWrite(PIN_EN_L_BWD, LOW);
      digitalWrite(PIN_EN_L_FWD, LOW);
      
      //motorLeft.setMotor(0);
      
      motorLeftReached = true;
    }
   if(!motorRightReached && ((int)motorRight._encoderVal >= abs((int)_stepsRight)))
    {
      INFO_iDRIVE("RIGHT STOP");
      
      //motorRight.setMotor(-1*SIGN(_stepsRight)*255); // FORCE STOP MOTOR
      //delay(1);
      //motorRight.setMotor(0);
      digitalWrite(PIN_EN_R_BWD, LOW);
      digitalWrite(PIN_EN_R_FWD, LOW);
      motorRightReached = true;
    }

    if(motorLeftReached && motorRightReached)
    {
      INFO_iDRIVE("END OF IDRIVE REACHED :) ");
      
      //INFO("L>"+String(motorLeft._encoderVal));
      
      t.stop(_checkStepsReachedId);
     /* solarPanel.adjustRoutine(SIGN(_stepsLeft)*motorLeft._encoderVal,SIGN(_stepsRight)* motorRight._encoderVal);*/
      
      INFO_iDRIVE("END of motor LEFT TICS is :" +String(motorLeft._encoderVal));
      INFO_iDRIVE("END of motor RIGHT TICS is :" +String(motorRight._encoderVal));
      
      motorLeft._encoderVal =0;
      motorRight._encoderVal=0;
      
      done();
    }
}


   

