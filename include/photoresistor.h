#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"


struct PhotoResistor {
    uint16_t adc_value;
    double light_level; // from 0.0 to 1.0
    double voltage; // 0 to 1.6v
    int id;
    
    void (*read_level) (struct PhotoResistor*); 

};

struct PhotoResistor* createPhotoResistor(int id);

void read_level(struct PhotoResistor*);




#endif