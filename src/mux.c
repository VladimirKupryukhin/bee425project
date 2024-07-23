#include "../include/mux.h"


struct MUX* createMux(int pin0, int pin1, int pin2, int pin3, int enablePin){
    printf("creaing mux\n");
    struct MUX* object = (struct MUX*)malloc(sizeof(struct MUX));

    object->controlPin0GPIO = pin0;
    object->controlPin1GPIO = pin1;
    object->controlPin2GPIO = pin2;
    object->controlPin3GPIO = pin3;

    object->enabledPinGPIO = enablePin;

    object->selectInput = &selectInput;


    gpio_init(pin0);
    gpio_set_dir(pin0, GPIO_OUT);
    gpio_put(pin0, 0);

    gpio_init(pin1);
    gpio_set_dir(pin1, GPIO_OUT);
    gpio_put(pin1, 0);

    gpio_init(pin2);
    gpio_set_dir(pin2, GPIO_OUT);
    gpio_put(pin2, 0);

    gpio_init(pin3);
    gpio_set_dir(pin3, GPIO_OUT);
    gpio_put(pin3, 0);

    gpio_init(enablePin);
    gpio_set_dir(pin3, GPIO_OUT);
    gpio_put(enablePin, 0);

    return object;

}



void selectInput(struct MUX* object, int input){
    printf("asdasasdadasas\n");
    int pinvalue0 = input & (1UL << 0);
    int pinvalue1 = (input & (1UL << 1)) >> 1;
    int pinvalue2 = (input & (1UL << 2)) >> 2;
    int pinvalue3 = (input & (1UL << 3)) >> 3;

    printf("Selecting: %d%d%d%d", pinvalue0, pinvalue1, pinvalue2, pinvalue3);

    gpio_put(object->controlPin0GPIO, pinvalue0);
    gpio_put(object->controlPin1GPIO, pinvalue1);
    gpio_put(object->controlPin2GPIO, pinvalue2);
    gpio_put(object->controlPin3GPIO, pinvalue3);
}