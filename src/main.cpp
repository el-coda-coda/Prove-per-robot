#include <Arduino.h>
#include <Servo.h>
#include "config.h"
#include "engine.h"
#include "serialReader.h"
#include "cutter.h"

engine motor;
cutter cut;

void setup(){
    Serial.begin(115200);
    motor.setup();
    motor.off();
    cut.setup();
}

void loop(){
    //driving engines 
    motor.on(engineThereshold, commandRead());
    if(commandRead() == OFF)    motor.off();
    cut.on(commandRead());
    //cutter engine
    if(commandRead() == CUT_OFF)    cut.off();
    delay(200);
}