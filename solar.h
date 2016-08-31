/*#ifndef SOLAR_H
#define SOLAR_H

class solar{
  public:
    solar(int stepsPerMM, int frameRad, int maxSpeed, int acceleration);      // sets currentAngle, stepsperMM and frameRadius
    void adjustRoutine(int stepsleft, int stepsRight); // receives both the # steps left and right encoder, check new positon on angle or on current sensor based
    //void currentControl();                    // position (& calibrate) based on current sensor reading
    //void stepsControl(int stepsleft, int stepsRight); // deltaPositon based control
      int dAngle(int stepsleft, int stepsRight); // returns dAngle based on dsteps, framerad and stepsperMM to new angle
      //int newAngle(void); // calculates the new angle based on dAngle and _currentAngle
      //void motorOn(int onTime); // set the motor on for x ms
      
      // sets currentAngle after command executed
    
    
    
  private:
    int _currentAngle; // deg
    int _stepsPerCM; 
    int _frameRadMM; // mm
    
    int _angleTurned;     // the total angle turned since last current sensor based calibration
    int _numAdjustments;  // the number of performed adjustments since last current sensor based calibration
};



#endif*/
