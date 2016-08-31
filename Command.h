#ifndef COMMAND_H
#define COMMAND_H

#include "Common.h"
#include "Instruction.h"



class Command {
    public:
        int   handler();
        int   readInput();
        int   processCommand();
        int   extractCommand();
        char  getCommandId();
        bool  isQueInstruction      (unsigned char commandId);
        bool  isDirectInstruction   (unsigned char commandId);
        void readNow(void);
        Command();
        int   addInstructionToQueue (Instruction * pInstr);

        char inData[20];            // Allocate some space for the string
        char inChar;                // Where to store the character read
        int index;                  // Index into array; where to store the character
        instrTypesEnum CMD;
};

#endif
