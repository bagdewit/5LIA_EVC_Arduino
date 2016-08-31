#include "ultra.h"
#include "definitions.cpp"
#include <Arduino.h> 

ultra::ultra(int trigPin,int echoPin,int timeoutMs, int numReadings, int maxDistance){
  INFO_ULTRA("SETTINGUP ULTRASONIC");
  _trigPin = trigPin;
  _echoPin = echoPin;
  _timeoutMs = timeoutMs;
  _numReadings = numReadings;
  _maxDistance = maxDistance;

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
};

unsigned int ultra::getDistance(void){
  INFO_ULTRA("ULTRA:GET DISTANCE");

  int * readings = new int [_numReadings];
  long duration;
  int distance;
  for(int i=0; i<_numReadings;i++)
  {
    INFO_ULTRA("NEXT READING");
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);
     INFO_ULTRA("Wait trigger");
    duration = pulseIn(_echoPin, HIGH, 60000);// _timeoutMs >> 10); // ms to microseconds
     INFO_ULTRA("triggered");
    int distance = (duration/2) / 29.1;
    if ((distance < _maxDistance) && (distance > 0))
      readings[i] = distance ;  // ^= *0.34
    else if (distance == 0)
      readings[i] = 0;
    else
      readings[i] = _maxDistance;
  }
  int sumDistances= 0;
  for(int j=0;j<_numReadings;j++)
  {
    sumDistances += readings[j];
  }

  
  delete[] readings;
  
  return (sumDistances / _numReadings);
  
}
