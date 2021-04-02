#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <QMC5883LCompass.h>
#include <LiquidCrystal_I2C.h>
#include <config.h>
#include <log.h>
#include <sensors.h>
#include <QMC5883.h>
#include <engines.h>
#include <segments.h>

void setup() {
  pinMode(PANEL_PIN, OUTPUT);
  LOG_LEVEL = INFO;
  Wire.begin();
  Serial.begin(115200); 
  engineSET();
  sensor.setCompass(FLAT);
  write.info(String("BAT: ") + String(sensor.battery()) + String(" %"));

  delay(5000);
}

void loop() {
  Serial.println("Still alive");
  write.info(String("DG: ") + String(sensor.compass()));
  delay(500);
}