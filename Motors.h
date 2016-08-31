#ifndef MOTORS_H
#define MOTORS_H

enum whichMotor {LEFT,RIGHT};


class motor {
    public:
        void setMotor(const int ciSpeed);
        motor(int pin_PWM, int pin_EN_FWD,int pin_EN_BWD, int pin_ENC, whichMotor motorSide);
        void motorDemo(void);
        void encoderCount(void);
        int _encoderVal;
    private:
        int _pin_PWM;
        int _pin_EN_FWD;
        int _pin_EN_BWD;
        int _pin_ENC;
        
};

#endif
