#include "pico/stdlib.h"
#include "../include/servo.h"
#include "../include/photoresistor.h"
#include "../include/mux.h"
#include "hardware/adc.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    stdio_init_all();
    adc_init();

    // This is the LED
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);

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

    struct PhotoResistor* light = createPhotoResistor(0);

    struct MUX* mux = createMux(21,20,19,18,22);
    mux->selectInput(mux, 14);


    while(true){
        printf("Raw Value: 0x%03x\n", light->adc_value );
        printf("Voltage Value: %f\n", light->voltage );
        printf("Light Value: %f\n", light->light_level );

        light->read_level(light);
        //const float conversion_factor = 3.3f / (1 << 12);
        //uint16_t result = adc_read();
        //printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
        sleep_ms(200);


        // printf("angle: %f\n", turntableMotor->currentAngle);
        // turntableMotor->setAngle(turntableMotor, angle);
        // yawMotor->setAngle(yawMotor, angle);

        // angle += step;

        // if (angle > 180 || angle < 10) {
        //     step *= -1;
        // }
    }

    return 0;
}