#include "../include/servo.h"


struct ServoMotor* createServoMotor(int gpioPinPWM) {

    printf("1\n");
    struct ServoMotor* motorObject = (struct ServoMotor*) malloc(sizeof(struct ServoMotor));

    printf("2\n");
    // set the function pointers
    motorObject->setAngle = &setAngle;
    motorObject->degree2radian = &degree2radian;
    motorObject->radian2degree = &degree2radian;

    printf("3\n");
    // set the variables
    motorObject->gpioPinPWM = gpioPinPWM;
    motorObject->currentDuty = 0;
    motorObject->currentAngle = 0;

    printf("4\n");
    // initialize the gpio pin for pwm
    gpio_set_function(motorObject->gpioPinPWM, GPIO_FUNC_PWM);

    motorObject->gpioSlice = pwm_gpio_to_slice_num(motorObject->gpioPinPWM);
    motorObject->gpioChannel = pwm_gpio_to_channel(motorObject->gpioPinPWM);

    // This makes the counter go up every 250th clock cycle
    // thus giving us a frequency of 500kHz
    pwm_set_clkdiv(motorObject->gpioSlice, 250.0);

    // This will make the TOP value be 10,000
    // Meaning that the counter will reset every 10,000th
    // counter value
    // This gives us a frequency of 50Hz
    // 10,000 correlates to 100% duty cycle
    pwm_set_wrap(motorObject->gpioSlice, 10000);

    // Default position is in the middle, meaning 90 degrees
    motorObject->setAngle(motorObject, 90);

    pwm_set_enabled(motorObject->gpioSlice, true);


}


void setAngle(struct ServoMotor* object, double target) {
    object->currentAngle = target;
    int newTargetLevel = (target * 10000) / 180.0;
    pwm_set_chan_level(object->gpioSlice, object->gpioChannel, newTargetLevel);
}

double degree2radian(double degree){

    return 0.0;
}

double radian2degree(double radian){
    return 0.0;
}






