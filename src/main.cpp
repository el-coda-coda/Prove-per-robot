#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include <EEPROM.h>
#include <QMC5883LCompass.h>
#include <LiquidCrystal_I2C.h>
#include <config.h>
#include <log.h>
#include <sensors.h>
#include <engines.h>
#include <QMC5883.h>
#include <calculates.h>
#include <segments.h>
#include <cutting.h>

void setup() {
  pinMode(LED_SETUP, OUTPUT);
  pinMode(PANEL_PIN, OUTPUT);
  digitalWrite(LED_SETUP, HIGH);
  LOG_LEVEL = INFO;
  Wire.begin();
  Serial.begin(115200); 
  engineSET();
  sensor.setCompass(CUSTOM);
  esc.attach(CUTTER_PIN);
  cutter.setup();
  write.info(String("BAT: ") + String(sensor.battery()) + String(" %"));

  delay(2000);
  write.verbose(String("First compass: ") + compassReadMedia());
  digitalWrite(LED_SETUP, LOW);
}

void loop() {
  if(Serial.available()){
    String command = Serial.readString();
    Serial.print(String(command));
    if (command.startsWith("-ON")) digitalWrite(LED_SETUP, HIGH);
    if (command.startsWith("-OFF"))  digitalWrite(LED_SETUP, LOW);
    if (command.startsWith("-STRAIGHT")){
       int x = (command.substring(9).toInt());
       segmentStraight(STRAIGHT, x);
    }
    if (command.startsWith("-RIGHT")){
     int x = (command.substring(6).toInt());
     Serial.print(String(command.substring(6)));
     segmentCURVE(x, RIGHT, compassReadMedia());
    }
    if (command.startsWith("-LEFT")){
     int x = (command.substring(5).toInt());
     Serial.print(String(command.substring(5)));
     segmentCURVE(x, LEFT, compassReadMedia());
    }
    if (command.startsWith("-STOP")) engineOFF();
    if (command.startsWith("-BACK"))  engineON(enginePWR, BACK);
    if (command.startsWith("-CALIBRATION")){
      engineON(50, RIGHT);
      qmcCalibration();
      engineOFF();
    }
    if (command.startsWith("-CUT OFF")) cutter.off();
    if (command.startsWith("-CUT ON")){
      int x = (command.substring(7).toInt());
      Serial.print(String(command.substring(7)));
      cutter.on(x);
    }

    if (command.startsWith("-CUT OPEN")) esc.writeMicroseconds(2000);
  }
}