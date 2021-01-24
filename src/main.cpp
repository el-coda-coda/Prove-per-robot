#include <Arduino.h>
#include <Wire.h>
#include <QMC5883LCompass.h>
#include <LiquidCrystal_I2C.h>
#include <config.h>
#include <log.h>
#include <motors.h>
#include <QMC5883.h>

LOG_LEVEL = INFO;

void setup() 
{
  Wire.begin();
  Serial.begin(115200); 
  engineSET();
  compassSET();
}

void loop() {
  // put your main code here, to run repeatedly:
}