#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <QMC5883LCompass.h>
#include <LiquidCrystal_I2C.h>
#include <config.h>
#include <log.h>
#include <sensors.h>
#include <QMC5883.h>
#include <calculates.h>
#include <engines.h>
#include <segments.h>

void setup() {
  pinMode(LED_SETUP, OUTPUT);
  pinMode(PANEL_PIN, OUTPUT);
  digitalWrite(LED_SETUP, HIGH);
  LOG_LEVEL = INFO;
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
  if(Serial.available()){
    String command = Serial.readString();
    Serial.print(String(command));
    if (command.startsWith("-ON")) digitalWrite(LED_SETUP, HIGH);
    if (command.startsWith("-OFF"))  digitalWrite(LED_SETUP, LOW);
    if (command.startsWith("-STRAIGHT")) engineON(100, STRAIGHT);
    if (command.startsWith("-STOP")) engineOFF();
    if (command.startsWith("-RIGHT 90"))  segmentCURVE(90, RIGHT, compassReadMedia());
    if (command.startsWith("-LEFT 90"))  segmentCURVE(90, LEFT, compassReadMedia());
  }
}