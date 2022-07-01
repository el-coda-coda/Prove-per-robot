#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include "config.h"
#include "engine.h"
#include "cutter.h"
#include "sensors.h"
#include "serialReader.h"

void setup(){
    Serial.begin(115200);
    delay(1000);
    Serial.println("HELLO :)");
    motor.setup();
    motor.off();
    cut.setup();

    //pinMode
    pinMode(SWITCH_PANEL_PIN, OUTPUT);
}

void loop(){
    //general
    turnOff();
    //driving engines
    motor.on(engineThereshold, commandRead());
    //cutter engine
    cut.on(commandRead());
    delay(500);
}