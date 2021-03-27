#include <Arduino.h>
#include <Wire.h>
#include <QMC5883LCompass.h>
#include <LiquidCrystal_I2C.h>
#include <config.h>
#include <log.h>
#include <sensors.h>
#include <engines.h>
#include <QMC5883.h>
#include <segments.h>

void setup() {
  pinMode(Panel_PIN, OUTPUT);

  LOG_LEVEL = INFO;
  Wire.begin();
  Serial.begin(115200); 
  engineSET();
  compassSET();
}

void loop() {
  engineON(255, LEFT);
  write.info(String(compassReadFast()));
  delay(500);
  engineOFF();
  delay(2000);
}