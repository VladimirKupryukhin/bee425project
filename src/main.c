#include "pico/stdlib.h"
#include "../include/servo.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    stdio_init_all();

    // This is the LED
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    // Blink 5 times in 10 seconds
    for (int index = 0; index < 10; index++) {
        gpio_put(25,index % 2);
        sleep_ms(1000);
        printf("%d \n", index);
    }


    struct ServoMotor* turntableMotor = createServoMotor(15);
    struct ServoMotor* yawMotor = createServoMotor(14);

    int angle = 10;//idk 0 kinda bends the thing
    int step = 10;

    while(true){
        printf("angle: %f\n", turntableMotor->currentAngle);
        turntableMotor->setAngle(turntableMotor, angle);
        yawMotor->setAngle(yawMotor, angle);

        angle += step;

        if (angle > 180 || angle < 10) {
            step *= -1;
        }

        sleep_ms(200);
    }

    return 0;
}