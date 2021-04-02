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
  pinMode(PANEL_PIN, OUTPUT);
  LOG_LEVEL = INFO;
  Wire.begin();
  Serial.begin(115200); 
  engineSET();
  compassSET();
  write.info(String(sensor.battery()));

  delay(5000);
}

void loop() {
  Serial.println("Still alive");
  write.info(String("DG: " + compassReadFast()));
  delay(500);
}