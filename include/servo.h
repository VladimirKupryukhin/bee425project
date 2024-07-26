#ifndef SERVO_H
#define SERVO_H
#define SERVO_FREQUENCY_CYCLE 50 //in hertz
#define SERVO_180_DEGREE_DUTY_CYCLE_US 2500 //micro seconds
#define SEVO_0_DEGREE_DUTY_CYCLE_US 1500 // micro seconds

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>
#include <stdlib.h>

struct ServoMotor{
    double currentAngle; //in degrees

    //GPIO stuff. Take a look at the Pico PWM documentation
    int gpioPinPWM;
    int gpioSlice;
    int gpioChannel;

    void (*setAngle) (struct ServoMotor* object, double target); // Function pointer
    double (*degree2radian) (double degree);
    double (*radian2degree) (double radian);


};


struct ServoMotor* createServoMotor(int gpioPinPWM);

void setAngle(struct ServoMotor* object, double target);

double degree2radian(double degree);

double radian2degree(double radian);



#endif


