#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

struct PhotoResistor {
    uint16_t adc_value; // 12bit number: 4096
    double light_level; // from 0.0 to 1.0
    double voltage; // 0 to 3.0v; from testing, I find that the resistance can go very low
    int id;
    
    void (*read_level) (struct PhotoResistor*); 

};

// Creates the struct with the id
struct PhotoResistor* createPhotoResistor(int id);

// Reads from ADC0 and converts the value into voltage/light_level
void read_level(struct PhotoResistor*);




#endif