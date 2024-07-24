#ifndef MUX_H
#define MUX_H

#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>

struct MUX {
    int controlPin0GPIO;
    int controlPin1GPIO;
    int controlPin2GPIO;
    int controlPin3GPIO;

    int enabledPinGPIO;

    void (*selectInput) (struct MUX* object, int inputPin);

};


struct MUX* createMux(int pin0, int pin1, int pin2, int pin3, int enablePin);
void selectInput(struct MUX* object, int input);




#endif