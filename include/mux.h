#ifndef MUX_H
#define MUX_H

#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>

struct MUX {
    // THe multiplexor has four control pins that control 16 inputs
    int controlPin0GPIO;
    int controlPin1GPIO;
    int controlPin2GPIO;
    int controlPin3GPIO;

    //LO -> ENABLED
    //HI -> DISABLED
    int enabledPinGPIO;

    void (*selectInput) (struct MUX* object, int inputPin);

};

// Creates a MUX struct
struct MUX* createMux(int pin0, int pin1, int pin2, int pin3, int enablePin);

// Select the input of the MUX based on the input pin number [0,15]
void selectInput(struct MUX* object, int input);




#endif