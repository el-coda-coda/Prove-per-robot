#include <Arduino.h>
#include <Wire.h>
#include <QMC5883LCompass.h>
#include <LiquidCrystal_I2C.h>
#include <config.h>
#include <log.h>
#include <motors.h>



void setup() {
  Serial.begin(115200);
  log(engineSET());

}

void loop() {
  // put your main code here, to run repeatedly:
}