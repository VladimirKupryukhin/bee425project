#include "../include/photoresistor.h"


struct PhotoResistor* createPhotoResistor(int id){
    struct PhotoResistor* object = (struct PhotoResistor*)malloc(sizeof(struct PhotoResistor));


    object->adc_value = 0;
    object->light_level = 0.0;
    object->id = id;

    object->read_level = &read_level;

    return object;

}



void read_level(struct PhotoResistor* object){
    float conversion_factor = 3.3f / (1 << 12);
    object->adc_value = adc_read();
    object->voltage = object->adc_value * conversion_factor;

    // Voltage increases as darkness increases, hence the 1.0 - ...
    object->light_level = 1.0 - (1 / 3.0) * object->voltage;


    // clamp the values
    if (object->light_level < 0) {
        object->light_level = 0.0;
    }

    if (object->light_level > 3.0) {
        object->light_level = 3.0;
    }

}