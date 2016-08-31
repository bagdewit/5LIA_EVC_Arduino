#include "energy.h"
#include "Common.h"
#include "Arduino.h"
#include "Timer.h"
#include "Definitions.cpp"


//#define INFO_ENERGY(message) Serial.println(message)


void callbackReportEnergy0(void){
    
    energySolar.readProcedure();
    energyPi.readProcedure();
  };

energy::energy(int sensorPin,int numReadings, int interval,int sensorNum){
  INFO_ENERGY("REGISTER SENSOR");
  
  _sensorPin = sensorPin;
  _numReadings = numReadings;
  _interval = interval;
  _sensorNum = sensorNum;
  _sumEnergy = 0;

  if(sensorNum ==0){
     t.every(_interval, callbackReportEnergy0) ;
     INFO_ENERGY("REGISTER CALLBACK SENSOR 0");
  }
  
  };

void energy::readProcedure(void){
  
  long sumReadings = 0;
  for(int reading = 0;reading< (1<<_numReadings);reading++)
  {
    sumReadings += analogRead(_sensorPin);
    delay(1);
   // INFO_ENERGY("MEAS:"+String(analogRead(_sensorPin)) + "on pin:"+_sensorPin);
  }
  //INFO_ENERGY("SUM:: "+String(sumReadings));
  sumReadings = (sumReadings >> _numReadings); // average current current & remove offset
  //INFO_ENERGY("AVG:: "+String(sumReadings));
  sumReadings -=512;
  
  //INFO_ENERGY("before map: "+String(sumReadings));
  sumReadings = map(sumReadings,-512,512,-5000,5000);
  sumReadings = (sumReadings << 2) ;
  sumReadings -= (sumReadings * 0.06) ;
  
  if(sumReadings < 0)
    sumReadings = 0;
  //INFO_ENERGY("after map: "+String(sumReadings));
  unsigned long timeNow = millis();
  INFO_ENERGY("SESSOR: "+String(_sensorNum)+" AVG:"+String(sumReadings) + "dT: " + String(timeNow-_lastReading) + "add E: " + String((long)((sumReadings * (timeNow-_lastReading))>>10)));
  _sumEnergy += (long)((sumReadings * (timeNow-_lastReading))>>10); // A milisecond
  INFO_ENERGY("sumEnergy:"+String(_sumEnergy));
  com_buffer[31] = 'M';
  if(_sensorNum == 0)
  {
    com_buffer[23] = _sumEnergy && 0x000000ff; 
    com_buffer[22] = _sumEnergy && 0x0000ff00; 
    com_buffer[21] = _sumEnergy && 0x00ff0000; 
    com_buffer[20] = _sumEnergy && 0xff000000; 
    }
  else
  {
     com_buffer[27] = _sumEnergy && 0x000000ff; 
    com_buffer[26] = _sumEnergy && 0x0000ff00; 
    com_buffer[25] = _sumEnergy && 0x00ff0000; 
    com_buffer[24] = _sumEnergy && 0xff000000; 
    }
  _lastReading = timeNow;
   INFO_ENERGY("Current current:" + String(sumReadings) + "total E: "+String(_sumEnergy));
  
  };

