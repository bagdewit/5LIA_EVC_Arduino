#include "Instruction.h"
#include "definitions.cpp"
#include "Idrive.h"
#include "Iflush.h"
#include "iObject.h"

////////////////////////
//    Process command //
////////////////////////

Instruction::Instruction() {
    // constructor
    INFO_INSTRUCTION("CREATED INSTRUCTION OBJECT");

    // instrType set in child class
};


char Instruction::getId() {
    return _id;
}

instrTypesEnum Instruction::getInstrType(char instructionString[])
{
    INFO_INSTRUCTION("EXTRACT INSTRUCTION TYPE");

    // local cmd chararray
    char cmd[4]; // contains the command +'\0'
    cmd[3] = '\0'; // end chararray with '\0'

    // obtain the CMD
    for (int i = 1; i < 4; i++) {
        cmd[i - 1] = instructionString[i];
    }


    if (strcmp(cmd, "DRI") == 0) // DRIVE COMMAND
        return DRI;
    else if (strcmp(cmd, "FLU") == 0) // FLUSH COMMAND
        return FLU;
    else if (strcmp(cmd, "MEE") == 0) // MEEP COMMAND (test)
        return MEE;
    else if (strcmp(cmd, "SER") == 0)
        return SER;
    else if (strcmp(cmd, "OBJ") == 0) // // DISTANCE COMMAND
        return OBJ;
    else {
        INFO ("NO INSTR types match");
        return NONE;
    }
};

Instruction* Instruction::parseInstruction(char iString[]) {
    INFO_INSTRUCTION("PARSING INSSTRUCTION");

    // 1. get instruction type
    instrTypesEnum iType = Instruction::getInstrType(iString);
    INFO_INSTRUCTION("INSTR TYPE: " + String(iType));

    // 2. match type of instruction and create associated instruction object
    Instruction *pnewInstruction = NULL;
    if      (isDriveInstruction(iType)) {
        pnewInstruction = new iDrive (iString);

    }
    else if (isMeeInstruction(iType)) {

    }
    else if (isFlushInstruction(iType))
    {
        INFO_INSTRUCTION("parsed: flush instruction");
        pnewInstruction = new iFlush();
    }
    else if (isObjectInstruction(iType))
    {
        INFO_INSTRUCTION("parsed: object instruction");
        pnewInstruction = new iObject(iString);
    }
    else
    {
        INFO_INSTRUCTION("NO INSTRUCTION TYPE MATCH");
    }

    return pnewInstruction;

};

void Instruction::doExecute(){
    // execute the right instruction
    //Serial.println("EXEC");
    this->execute();

    // remove the instruction object
    //delete this;

    //return 0; possible after delete?
};

int freeRam () {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

void Instruction::done(){
  INFO_INSTRUCTION("DONE:heap:");
  //Serial.print("free:");
  //Serial.println(freeRam());
  QueueFlag = false; // process next item of que
  //Serial.println(freeRam());
  delete this;
  };
bool Instruction::isDriveInstruction(instrTypesEnum instrType) {
    if (instrType == DRI) { // DRIVE COMMAND
        INFO_INSTRUCTION("DRIVE INSTRUCTION");
        return true;
    }
    return false;
};


bool Instruction::isFlushInstruction(instrTypesEnum instrType) {
    if (instrType == FLU) { // DRIVE COMMAND
        INFO_INSTRUCTION("FLUSH INSTRUCTION");
        return true;
    }
    return false;
};

bool Instruction::isObjectInstruction(instrTypesEnum instrType) {
    if (instrType == OBJ) { // OBJECT CHECK COMMAND
        INFO_INSTRUCTION("OBJ INSTRUCTION");
        return true;
    }
    return false;
};



bool Instruction::isMeeInstruction(instrTypesEnum instrType) {
    if (instrType == MEE) { // MEE COMMAND
        INFO_INSTRUCTION("MEE INSTRUCTION");
        return true;
    }
    return false;
};

void Instruction::test() {
    INFO_INSTRUCTION("INSTRUCTION.test called succesfully!");
}

char Instruction::obtainId(char *iString) {
    return iString[0]; // common for all instructions
};
