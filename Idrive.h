#ifndef IDRIVE_H
#define IDRIVE_H
#include "Instruction.h"

class iDrive : public Instruction {
    public:
        iDrive(char *iString);
        void execute();
        void checkStepsReached(void);
    private:
        int obtainStepsLeft(char * iString);
        int obtainStepsRight(char * iString);
        int obtainDuration(char * iString);
        
        int _stepsLeft;
        int _checkStepsReachedId;
        unsigned int _duration;
        int _stepsRight;
        int test;
};

#endif

#define MOTORSPEED 255
#define MOTORLEFTOFFSET 1.12
#define MOTORRIGHTOFFSET 1.25
