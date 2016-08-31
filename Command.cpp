#include "Command.h"
#include <Arduino.h>
#include "definitions.cpp"
#include "Common.h"
#include "Instruction.h"
#include <Wire.h>

///////////////////
//    COMMANDS   //
///////////////////



Command::Command() {
    inChar = -1;
    index = 0;
};


char Command::getCommandId() {
    return inData[0]; // return command Identifier
};

bool Command::isQueInstruction(unsigned char commandId) {
    INFO_COMMAND(String((int) commandId));
    if ((int)commandId <= 127)
        return true;
    return false;
};

bool Command::isDirectInstruction(unsigned char commandId) {
    INFO_COMMAND(String((int) commandId));
    if ((int)commandId == ID_DIRECT_INSTRUCTION)
        return true;
    return false;
};

int Command::addInstructionToQueue(Instruction * pInstr) {
    // create que struct
    pQueueInstruction newPQueue;
    // link queue struct to the new instruction
    newPQueue.pInstr = pInstr;
    // add this linked instruction to the queue
    queue.push(newPQueue); // todo: add if success and if not success!
    // obtain queue size
    byte queueSize = (byte)queue.count();
    // acknowledge pi
    //Serial.print('A'); Serial.print(pInstr->getId()); Serial.print("Q"); Serial.print(queueSize);Serial.print("\n");
    // debug log:
    INFO_COMMAND("Instructions in queue:" + String(queueSize));

    return 0; // todo
};
   

void Command::readNow(){
  ProcessInputFlag = false;
  int idx=2;
    if (idx > 1) // more than 1 char read
    {
        Serial.println("I2:" + String(inData));

        unsigned char commandId = getCommandId();
        INFO_COMMAND("RECEIVED STRING of length:" + String(idx));
        INFO_COMMAND("COMMAND ID: " + String((int)commandId));

        if (isQueInstruction(commandId))
        {
            INFO_COMMAND("QUEUE INSTRUCTION");
            com_buffer[0] = 'A';
            com_buffer[1] = commandId;
            
            Instruction *pNewInstruction = Instruction::parseInstruction(inData); // creates object of right instruction type
            if (pNewInstruction!=NULL) {
                com_buffer[0] = 'A';
                com_buffer[1] = commandId;
                addInstructionToQueue(pNewInstruction); // add to next instruction in queue
            } else {
                com_buffer[0] = 'N';
                com_buffer[1] = 'N';
            }
        }
        else if (isDirectInstruction(commandId))
        {
            INFO_COMMAND("DIRECT INSTRUCTION");
            Instruction *pNewInstruction = Instruction::parseInstruction(inData); // creates object of right instruction type
            if (pNewInstruction!=NULL) {
                com_buffer[0] = 'A';
                com_buffer[1] = commandId;
                pNewInstruction->doExecute(); // execute directly
                delete pNewInstruction;
            } else {
                com_buffer[0] = 'N';
                com_buffer[1] = 'N';
            }
        }
        else
        {
            INFO_COMMAND("NO INSTRUCTION TYPE MATCH"+String(commandId));
            com_buffer[0] = 'N';
            com_buffer[1] = 'N';
        }

        // reset the variables
        index = 0;
        for (int i = 0; i < 20; i++)
            inData[i] = '\0'; // reset indata

    }else {
        //1 or 0 chars read, TODO
    }
    
  };
int Command::handler() {
    int idx = readInput();
   // int idx = 2;
    ProcessInputFlag = true;
    //Serial.println("flag:"+String(ProcessInputFlag));
    return 0; //todo
};

int Command::readInput() {
  ProcessInputFlag = false;
    index = 0;

    if (Wire.available() > 18){
        INFO("ERROR, too many characters");
         while (Wire.available()) { // loop through all
           Wire.read(); // clear
         }
        return 0;
    }

    while (Wire.available()) { // loop through all
        inData[index] = Wire.read(); // Store it
        index++; // Increment where to write next
        inData[index] = '\0'; // Null terminate the string in case it is last character
    }

    INFO_COMMAND(inData); // PRINT received input over I2C
    return index;
}



