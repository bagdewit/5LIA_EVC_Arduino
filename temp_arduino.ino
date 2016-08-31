

/////////////////
//  INCLUDES   //
/////////////////
#include <QueueList.h>
/*#include <LiquidCrystal.h>*/
#include <Servo.h>
#include <Wire.h>
#include "definitions.cpp"
#include "Command.h"
#include "Instruction.h"
#include "Common.h"
#include "Timer.h"

/////////////////
// DEFINITIONS //
/////////////////


////////////////////
// PROTOFUNCTIONS //
////////////////////

void processCommand(char *inData);
int QUE_CMD_DRI(char *inData);
int QUE_CMD_FLU(char *inData);
int QUE_CMD_MEE(char *inData);
bool CMD_DRI(struct INSTR instruction);
bool CMD_FLU(struct INSTR instruction);
bool CMD_MEE(struct INSTR instruction);
void ENC_COUNT_L(void);
void ENC_COUNT_R(void);


/////////////////////
// DATA STRUCTURES //
/////////////////////

// the command structs/ instruction types
struct CMD_DRIVE {
  int stepsLeft;
  int stepsRight;
};

struct CMD_SERVO {
  int id;
  int angle;
};

///////////////////
//   VARIABLES   //
///////////////////

Servo myservo;
QueueList <pQueueInstruction> queue;
/*LiquidCrystal lcd(8, 9, 4, 5, 6, 7);// EXTERN*/

Timer t;

extern motor motorLeft  (PIN_PWM_L, PIN_EN_L_FWD,PIN_EN_L_BWD, PIN_ENC_L,LEFT);
extern motor motorRight (PIN_PWM_R, PIN_EN_R_FWD,PIN_EN_R_BWD, PIN_ENC_R,RIGHT);
//AccelStepper yawStepper(AccelStepper::FULL4WIRE, PIN_STEPPER_IN1, PIN_STEPPER_IN2, PIN_STEPPER_IN3, PIN_STEPPER_IN4, true);
/*solar solarPanel(MOTOR_STEPS_PER_CM*1.75, CAR_FRAME_RAD_MM, STEPPER_MAX_SPEED, STEPPER_ACCELERATION);*/

extern energy energySolar(PIN_ENERGY_SOLAR  ,ENERGY_SOLAR_NUMREADINGS, ENERGY_SOLAR_INTERVAL,0);
extern energy energyPi   (PIN_ENERGY_PI     ,ENERGY_SOLAR_NUMREADINGS, ENERGY_SOLAR_INTERVAL,1);

extern bool ProcessInputFlag = false;
ultra ultraFront        (PIN_ULTRA_FRONT_TRIG,PIN_ULTRA_RRONT_ECHO,ULTRA_FRONT_TIMEOUTMS,ULTRA_FRONT_NUM_READINGS,ULTRA_FRONT_MAX_DISTANCECM);

unsigned long timer_10000; // the timer
unsigned long INTERVAL_10000 = 6000; // the repeat interval

//LiquidCrystal lcd(8, 9, 4, 5, 6, 7);// EXTERN
Command nextCommand;

bool QueueFlag;
unsigned char com_buffer[32];

void testt(){};

void requestEvent() {
  Wire.write(com_buffer,32);
  
}


int processQueue(void) {

  //INFO("processQueue started");
  // if que is enmpty, return
  if (queue.count() == 0)
    return 0;
  QueueFlag = true;
  //INFO("#instructions in queue:"+String(queue.count()));
  //Serial.println("N#"+String(queue.count()));
  // obtain next instruction from queue
  //INFO("obtain next instruction from queue");
  pQueueInstruction nextInstrStruct = queue.peek();

  // execute next instruction from que INDEPENDANT of instr type!! YES!! :) automatically deletes the object after performed execution
  nextInstrStruct.pInstr->doExecute();
  //INFO("NE");
  // remove instruction from queue
  queue.pop();

  if (true) { // todo: when to send DACK? specifications?
    /*Serial.print("D");
    Serial.print(nextInstrStruct.pInstr->getId());
    Serial.print("\n");*/

  }

  return 0; // succcess

}


void wireCallback(int howMany){
  //Serial.println(">i");
  nextCommand.handler();
  
  }

void setup () {
  ///////////////
  //    INIT   //
  ///////////////

  // start serial communication.
  Serial.begin (9600);
  queue.setPrinter (Serial);

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(wireCallback); // register event
  Wire.onRequest(requestEvent); // register event
  //initialize ledscreen
  /*lcd.begin(16, 2);              // start the library
  LCD("Hello dear Solar",""); // print a simple message*/

  // init servo
  myservo.attach(PIN_SERVO);  // attaches the servo on pin 9 to the servo object

  // first motor run
  
  #ifdef INIT_MOTOR_DEMO
    //motorDemo();
  #endif
    timer_10000 = millis(); // start timer
    QueueFlag = false;
    Serial.println("START");
//solarPanel.adjustRoutine(motorLeft._encoderVal, motorRight._encoderVal);

  /*
  char Command[] = "2DRI+900-9005000";  // 512 half turn, 0.5 circle,33 cm, 512 steps
  for(int i = 0; i< sizeof(Command); i++)
  {
    nextCommand.inData[i] = Command[i];
  }
  nextCommand.readNow();
  char  Command2[] = "2DRI+900+9005000";  // 512 half turn, 0.5 circle,33 cm, 512 steps
  for(int i = 0; i< sizeof(Command); i++)
  {
    nextCommand.inData[i] = Command2[i];
  }
  nextCommand.readNow();
  
    char Command3[] = "2DRI-900+9005000";  // 512 half turn, 0.5 circle,33 cm, 512 steps
  for(int i = 0; i< sizeof(Command); i++)
  {
    nextCommand.inData[i] = Command3[i];
  }
  nextCommand.readNow();
  
  /*char Command2[] = "2DRI+000+9995000";
  for(int i = 0; i< sizeof(Command); i++)
  {
    nextCommand.inData[i] = Command[i];
  }
  nextCommand.readNow();char Command3[] = "2DRI+000+9995000";
  for(int i = 0; i< sizeof(Command); i++)
  {
    nextCommand.inData[i] = Command[i];
  }
  nextCommand.readNow();
  for(int i = 0; i< sizeof(Command); i++)
  {
    nextCommand.inData[i] = Command[i];
  }
  nextCommand.readNow();
  
  /*
  char Command2[] = "2OBJA";
  for(int i = 0; i< sizeof(Command2); i++)
  {
    nextCommand.inData[i] = Command2[i];
  }
  nextCommand.readNow();*/
  
} 


bool stepperOn = true;

void loop () {
//yawStepper.run();
  
//    if(!yawStepper.run() )
//    {
//      yawStepper.disableOutputs();
//      com_buffer[31] = 'D';
//      //Serial.println("DISABLE");
//     
//      //stepperOn=false;
//    }
    if(ProcessInputFlag == true){
    nextCommand.readNow();
    }
  //INFO_SOLAR("POSITION: "+String(yawStepper.currentPosition()));
    if (QueueFlag == false) {
        processQueue(); // process que command (re)trigger
    }
     t.update();
     
}

