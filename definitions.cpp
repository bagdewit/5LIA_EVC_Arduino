#ifndef DEFINITIONS
#define DEFINITIONS

////////////////////
// COMPILE CONFIG //
////////////////////

// set the compile mode
//#define MODE_DEBUG
//#define PRINT_iOBJECT
//#define PRINT_ENERGY
//#define PRINT_SOLAR
//#define PRINT_INSTRUCTION
#define PRINT_iDRIVE

// do not change below this line

// set the associated compile flagg
#ifdef MODE_DEBUG
 //#define PRINT_INFO
 #define INIT_MOTOR_DEMO   // enables a motor demo at the setup of the arduino
#endif

// process compile flags
#ifdef PRINT_INFO
#define INFO(message) Serial.println(message)
#else
#define INFO(message)
#endif

#ifdef PRINT_COMMAND
  #define INFO_COMMAND(message) Serial.println(message)
#else
  #define INFO_COMMAND(message)
#endif

#ifdef PRINT_iDRIVE
  #define INFO_iDRIVE(message) Serial.println(message)
#else
  #define INFO_iDRIVE(message)
#endif


#ifdef PRINT_FLUSH
  #define INFO_FLUSH(message) Serial.println(message)
#else
  #define INFO_FLUSH(message)
#endif


#ifdef PRINT_INSTRUCTION
  #define INFO_INSTRUCTION(message) Serial.println(message)
#else
  #define INFO_INSTRUCTION(message)
#endif


#ifdef PRINT_MOTORS
  #define INFO_MOTORS(message) Serial.println(message)
#else
  #define INFO_MOTORS(message)
#endif


#ifdef PRINT_ULTRA
  #define INFO_ULTRA(message) Serial.println(message)
#else
  #define INFO_ULTRA(message)
#endif


#ifdef PRINT_iOBJECT
  #define INFO_iOBJECT(message) Serial.println(message)
#else
  #define INFO_iOBJECT(message)
#endif


#ifdef PRINT_ENERGY
  #define INFO_ENERGY(message) Serial.println(message)
#else
  #define INFO_ENERGY(message)
#endif



#ifdef PRINT_SOLAR
  #define INFO_SOLAR(message) Serial.println(message)
#else
  #define INFO_SOLAR(message)
#endif


// functions
#define LCD(row1,row2) lcd.setCursor(0,0);lcd.print(row1);lcd.setCursor(0,1);lcd.print(row2)
#define LCD_CLEAN()    lcd.setCursor(0,0);lcd.print("                ");lcd.setCursor(0,1);lcd.print("                ");
#define _3chars2dec(c)  ((int)*(c) - 48) * 100  + ((int)*(((char*)c)+1) - 48) * 10  + (int)*(((char *)c)+2) - 48                                    // pointer based
#define _4chars2dec(c)  ((int)*(c) - 48) * 1000 + ((int)*(((char*)c)+1) - 48) * 100 + ((int)*(((char*)c)+2) - 48) * 10 + (int)*(((char *)c)+3) - 48 // pointer based
#define SIGN(i) ((i>=0)?1:-1)

// instructions
#define MAX_ID_QUE_INSTRUCTION 127
#define ID_DIRECT_INSTRUCTION 128

// pin connections
#define PIN_SERVO 10

#define PIN_PWM_L 9         // left motor enable pin
#define PIN_PWM_R 5         // right motor enable pin

#define PIN_EN_L_BWD 8      // left motor forward pin
#define PIN_EN_L_FWD 4      // left motor backwards pin

#define PIN_EN_R_BWD 6      // right motor formward pin
#define PIN_EN_R_FWD 7      // right motor backwards pin

#define PIN_ENC_L 2        // left motor encoder pin
#define PIN_ENC_R 3        // right motor encoder pin

#define PIN_ULTRA_FRONT_TRIG  48  // ultrason trigger pin
#define PIN_ULTRA_RRONT_ECHO 50  // ultrasone echo pin

#define PIN_ENERGY_SOLAR  1 
#define PIN_ENERGY_PI     0

#define PIN_STEPPER_IN1 51
#define PIN_STEPPER_IN2 49
#define PIN_STEPPER_IN3 47
#define PIN_STEPPER_IN4 45

// current sensor
#define ENERGY_SOLAR_INTERVAL 1000 // interval in ms
#define ENERGY_SOLAR_NUMREADINGS 7 // number of readings for averaging (2^n!!!)

#define ENERGY_PI_INTERVAL 1000 // interval in ms
#define ENERGY_PI_NUMREADINGS 7 // number of readings for averaging (2^n!!!)
// wheel motor: JGA25-371 DC gearmotor

#define CAR_FRAME_RAD_MM 425 // half of between wheel base distance in mm (425mm)
#define MOTOR_STEPS_PER_CM 15.5
// motor, 12 ticks/ rev, 1:34 gear reduction  = 408 ticks per rev
// 1 rev is 2*pi*(8.4cm diameter wheels/2) = 2*pi*4.3=26.4cm
// 408/26.4 = 15.5 ticks per cm


// solar panel stepper
#define STEPS_PER_MOTOR_REVOLUTION 32    //---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
#define STEPS_PER_OUTPUT_REVOLUTION (32 * 64)  //2048   // gear ratio = 64:1, with a 4 step sequence

#define STEPPER_MAX_SPEED 500
#define STEPPER_ACCELERATION 5300
//ultrasone sensor front (shadow detect):
#define ULTRA_FRONT_TIMEOUTMS 10 // max 2 meter, 230m/s =6.7 ms, add some extra
#define ULTRA_FRONT_NUM_READINGS 5 // number of readings which will be averaged before returning reslt;
#define ULTRA_FRONT_MAX_DISTANCECM 200
#endif
