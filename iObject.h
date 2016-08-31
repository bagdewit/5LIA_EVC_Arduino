#ifndef IDIST_H
#define IDIST_H


#include "Instruction.h"

class iObject : public Instruction{
  public:
  iObject(char * iString);
  void execute(void); 
  private:
  unsigned int _clearDistance; 
};


#endif
