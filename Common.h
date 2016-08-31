#ifndef COMMON_H
#define COMMON_H

#include <QueueList.h>
/*#include <LiquidCrystal.h>*/
#include <Servo.h>
#include "Motors.h"
#include "Timer.h"
#include "Ultra.h"
#include "energy.h"
#include "AccelStepper.h"
/*#include "solar.h"*/

// COMMANDS TYPES
enum instrTypesEnum {NONE, DRI, MEE, SER, FLU, OBJ}; // list of all the instruction types: a.k.a. all the command structs used as opcode


class Instruction;
struct pQueueInstruction { // used for the queuelist
  Instruction * pInstr;
};

extern bool ProcessInputFlag;

extern bool QueueFlag;
extern motor motorLeft;
extern motor motorRight;
extern ultra ultraFront;
extern Timer t;
extern energy energySolar;
extern energy energyPi;
//extern AccelStepper yawStepper;
/*extern solar solarPanel;*/
// create a queue of datatype INSTR datatype
extern QueueList <pQueueInstruction> queue; // EXTERN

//lcd
/*extern LiquidCrystal lcd;// EXTERN*/

//servo
extern Servo myservo;  // create servo object to control a servo  // EXTERN
extern unsigned char com_buffer[32];
/*
 * 
 int freeRam () 
    {
      extern int __heap_start, *__brkval; 
      int v; 
      return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
    }*/
#endif
