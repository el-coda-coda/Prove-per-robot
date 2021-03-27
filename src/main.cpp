#include <Arduino.h>
#include <Wire.h>
#include <QMC5883LCompass.h>
#include <LiquidCrystal_I2C.h>
#include <config.h>
#include <Strings.h>
#include <log.h>
#include <engines.h>
#include <QMC5883.h>
#include <segments.h>

void setup() {
  LOG_LEVEL = INFO;
  Wire.begin();
  Serial.begin(115200); 
  engineSET();
  compassSET();
}

void loop() {
  segmentCURVE(10, LEFT);
  log(String(compassReadMedia()));
  delay(1000);
}