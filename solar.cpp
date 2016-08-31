/*#include "solar.h"
#include "AccelStepper.h"
#include "definitions.cpp"
#include "Common.h"


// solar panel stepper
//#define STEPS_PER_MOTOR_REVOLUTION 32    //---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
//#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048   //---( Steps per OUTPUT SHAFT of gear reduction )---



solar::solar(int stepsPerCM, int frameRadMM, int maxSpeed, int acceleration){
  
  _currentAngle = 0; // deg
  _stepsPerCM = stepsPerCM;//
  _frameRadMM = frameRadMM; // frameradius in mm
  

  // set stepper
  yawStepper.setMaxSpeed(maxSpeed);
  yawStepper.setAcceleration(acceleration);
  //yawStepper.setEnablePin(pinStepperEnable);
  //pinMode(_pinStepperEnable,OUTPUT);
  
  // demo
  //yawStepper.move(STEPS_PER_OUTPUT_REVOLUTION);
};


int solar::dAngle(int stepsLeft, int stepsRight){
  int dSteps = stepsLeft - stepsRight;
  int dtravelMM = (dSteps / (float)_stepsPerCM)*10; // mm 
  int circleOmtrek = 2*3.1415*(float)_frameRadMM; // mm
  int dAnglee = ( dtravelMM/ (float)(circleOmtrek)) * 360;
  INFO_SOLAR("dsteps: "+String(dSteps) + "dtravelMM: " + String(dtravelMM) + "circleOmtrek: " + String(circleOmtrek) + " dangle: "+String(dAnglee));
  
  return dAnglee;
};

void solar::adjustRoutine(int stepsLeft, int stepsRight){

  if(0)//(_angleTurned > 360) && (numAdjustments > 2) | ((_angleTurned > 90) && (numAdjustments > 5)) )
  {
    // perform current sensor based calibration
    INFO_SOLAR("CURRENT based calibration");
  }
  else
  {
    
    // set angle based on difference
    int dAnglee = dAngle(stepsLeft,stepsRight);
    INFO_SOLAR("POSITION: "+String(yawStepper.currentPosition()));
    // update current angle
    INFO_SOLAR("OLD_ANGLE: "+String(_currentAngle));
    _currentAngle = (_currentAngle + dAnglee); // -10=>350, 370=>350 etc
    INFO_SOLAR("NEW_ANGLE: "+String(_currentAngle));
    if(_currentAngle >= 0 )
      _currentAngle = _currentAngle % 360;
    if (_currentAngle < 0)
      _currentAngle = 360+_currentAngle;
    INFO_SOLAR("aftermodulo: "+String(_currentAngle));
    yawStepper.enableOutputs();//
    
    INFO_SOLAR("MOVE ABS: "+String((float)_currentAngle*STEPS_PER_OUTPUT_REVOLUTION/(float)360));
    yawStepper.moveTo((float)_currentAngle*STEPS_PER_OUTPUT_REVOLUTION/(float)360);
    
    
    //INFO_SOLAR("MOVEMENT STARTED");
    // calc on time
    
  }
  
};*/

