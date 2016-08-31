#ifndef ULTRA_H
#define ULTRA_H

class ultra{
  public:
    ultra(int trigPin,int echoPin,int timeoutMs, int numReadings, int maxDistance);
    unsigned int getDistance(void);
  private:
    int _timeoutMs;
    int _numReadings;
    int _trigPin;
    int _echoPin;
    int _maxDistance;
  };


#endif
