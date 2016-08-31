#include "iObject.h"
#include "Common.h"
#include "ultra.h"
#include "definitions.cpp"


iObject::iObject(char * iString){
  _clearDistance = iString[4];
  
}

void iObject::execute(void){
  int distance = ultraFront.getDistance();
  INFO_iOBJECT("DISTANCE: " + String(distance));
  if (distance < _clearDistance)
    {
      INFO_iOBJECT("OBJECT DETECTED!!");
      com_buffer[0] = 1;
    }
  else
    {
      INFO_iOBJECT("NO OBJECT DETECTED :)");
      com_buffer[0] = 0;
    }//return false;  // there is no object in the distance set!
    QueueFlag = false;
};
