#include <Arduino.h>
#include <Servo.h>
#include "config.h"
#include "engine.h"
#include "serialReader.h"
#include "cutter.h"

engine motor;

void setup(){
    Serial.begin(115200);
    motor.setup();
    motor.off();
}

void loop(){
    motor.on(engineThereshold, commandRead());
    if(commandRead() == OFF)    motor.off();

    delay(200);
}