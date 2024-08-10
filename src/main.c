#include "pico/stdlib.h"
#include "../include/servo.h"
#include "../include/photoresistor.h"
#include "../include/mux.h"
#include "hardware/adc.h"
#include <stdio.h>
#include <stdlib.h>

#define ESC "\x1B"
#define CLS ESC"[2J"
#define HOME ESC"[H"

void clear_to_top(void){
    printf(CLS);
    printf(HOME);
    fflush(stdout);
}

int HorizTilt(struct PhotoResistor**, struct ServoMotor*);
void GetValue(int num, struct MUX*, struct PhotoResistor**);
bool CmpValues(struct PhotoResistor*, struct PhotoResistor*);
int VertTilt(struct PhotoResistor**, struct ServoMotor*);

//Arbitrary value for determining if 2 photoresistors have the same light level
double tolerance = 0.05;


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

    //Allocates memory for an array of photoresistors
    struct PhotoResistor** light = (struct PhototResistor**)malloc(16*sizeof(struct PhotoResistor*));

    for(int i = 0; i < 16; i++){
        light[i] = createPhotoResistor(i);
    }
    
    struct MUX* mux = createMux(21,20,19,18,22);

    while(true){

    bool HorizDone;
    bool VertDone;

    printf("Photoresistor Light Levels:\n");

    //Get photoresistor values
      for(int i = 0; i < 16; i++){
            GetValue(i, mux, light);
            printf("Light Value %d: %f\n", i, light[i]->light_level );
        }

    printf("\nTilting Status:\n");

        //Execute hoirzontal tilt
        if(HorizTilt(light, turntableMotor) != 0){
            printf("Horizontal angle set at %.2f degrees\n", turntableMotor->currentAngle);
            HorizDone = true;    
        }
        else{ HorizDone = false;}   

        //Execute vertical tilt
        if(VertTilt(light, yawMotor) != 0 && HorizDone){
            printf("Vertical angle set at %.2f degrees\n", yawMotor->currentAngle);
            VertDone = true;   
        }
        else{ VertDone = false;}

        if(HorizDone && VertDone){
            printf("Found light source\n");
        }
        else{
            printf("Still searching...\n");
        }

        sleep_ms(500);
        clear_to_top(); //Clear console output
    }

    return 0;
}

//Compares the light levels of 2 photoresistors and returns true if they both fall within the tolerance range
bool CmpValues(struct PhotoResistor* l1, struct PhotoResistor* l2){
    double margin = (l1->light_level - l2->light_level) / tolerance;
    if(margin <= 1.0 && margin >= -1.0){
        return true;
    }
    else{ return false;}
}

//Gets the value of a specified photoresistor
void GetValue(int num, struct MUX* mux, struct PhotoResistor** light){
    mux->selectInput(mux, num);
    light[num]->read_level(light[num]);
}

//Tilts the platform horiztonally using turntableMotor
int HorizTilt(struct PhotoResistor** light, struct ServoMotor* motor){

    if(CmpValues(light[0], light[4]) && CmpValues(light[5], light[15]) && CmpValues(light[6], light[14]) && CmpValues(light[7], light[13]) && CmpValues(light[8], light[12])){
        return 1;
    }

    else if(motor->currentAngle >= 130.0 || motor->currentAngle <= 50.0){
        return 2;
    }

    else if(light[6]->light_level > light[14]->light_level){
        motor->setAngle(motor, motor->currentAngle + 1.0);
        return 0;
    }
    else{
        motor->setAngle(motor, motor->currentAngle - 1.0);
        return 0;
    }
}
    
//Tilts the platform vertically using yawMotor
int VertTilt(struct PhotoResistor** light, struct ServoMotor* motor){

    if(CmpValues(light[0], light[12]) && CmpValues(light[1], light[11]) && CmpValues(light[2], light[10]) && CmpValues(light[3], light[9]) && CmpValues(light[4], light[8])){
        return 1;
    }

    else if(motor->currentAngle >= 130.0 || motor->currentAngle <= 50.0){
        return 2;
    }

    else if(light[2]->light_level < light[10]->light_level){
        motor->setAngle(motor, motor->currentAngle + 1.0);
        return 0;
    }
    else{
        motor->setAngle(motor, motor->currentAngle - 1.0);
        return 0;
    }
}