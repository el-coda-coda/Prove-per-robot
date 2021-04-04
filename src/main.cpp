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
  pinMode(LED_SETUP, OUTPUT);
  pinMode(PANEL_PIN, OUTPUT);
  digitalWrite(LED_SETUP, HIGH);
  LOG_LEVEL = VERBOSE;
  Wire.begin();
  Serial.begin(115200); 
  engineSET();
  sensor.setCompass(FLAT);
  write.info(String("BAT: ") + String(sensor.battery()) + String(" %"));

  delay(5000);
  write.verbose(String("First compass: ") + compassReadMedia());
  digitalWrite(LED_SETUP, LOW);
}

void loop() {
  write.info(String("Start turn"));
  int deg_set = compassReadMedia();
  bool he = true;
  cdDeg(deg_set, LEFT, 90);
  write.info(String("Turning finished"));
  //write.info(String("DEG_DIFF: ") + compassDeg(compassReadMedia(), 90, LEFT));
  
  delay(5000);
}