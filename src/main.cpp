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
  pinMode(SWITCH_PANEL_PIN, OUTPUT);
  digitalWrite(CUTTER_PIN, LOW);
  LOG_LEVEL = INFO;
  Wire.begin();
  Serial.begin(115200); 
  esc.attach(CUTTER_PIN);
  cutter.setup();
  engineSET();
  sensor.setup();
  sensor.setCompass(CUSTOM);
  write.info(String("BAT: ") + String(sensor.battery()) + String(" %"));
  delay(2000);
}

void loop() {
  if(Serial.available()){
    String command = Serial.readString();
    Serial.print(String(command));
    /*if (command.startsWith("-ON")) digitalWrite(LED_SETUP, HIGH);
    if (command.startsWith("-OFF"))  digitalWrite(LED_SETUP, LOW);*/
    if (command.startsWith("-STRAIGHT")){
      int x = (command.substring(9).toInt());
      //segmentStraight(STRAIGHT, x);
      engineON(enginePWR, STRAIGHT);
    }
    if (command.startsWith("-RIGHT")){
      int x = (command.substring(6).toInt());
      Serial.print(String(command.substring(6)));
      segmentCURVE(x, RIGHT, sensor.compass());
    }
    if (command.startsWith("-LEFT")){
      int x = (command.substring(5).toInt());
      Serial.print(String(command.substring(5)));
      segmentCURVE(x, LEFT, sensor.compass());
    }
    if (command.startsWith("-STOP")) engineOFF();
    if (command.startsWith("-BACK"))  engineON(enginePWR, BACK);
    if (command.startsWith("-ENGINE POWER")){
      int x = (command.substring(13).toInt());
      Serial.print(String(command.substring(7)));
      enginePWR = x;
    }
    if (command.startsWith("-CALIBRATION")){
      engineON(enginePWR, RIGHT);
      qmcCalibration();
      engineOFF();
      firstCompass();
    }
    if (command.startsWith("-CUT OFF")) cutter.off();
    if (command.startsWith("-CUT ON")){
      int x = (command.substring(7).toInt());
      Serial.print(String(command.substring(7)));
      cutter.on(x);
    }
    if (command.startsWith("-CUT MAX")) esc.writeMicroseconds(2000);
    if (command.startsWith("-LVL INFO")) LOG_LEVEL = INFO;
    if (command.startsWith("-LVL DEBUG")) LOG_LEVEL = DEBUG;
    if (command.startsWith("-LVL VERBOSE")) LOG_LEVEL = VERBOSE;
    if (command.startsWith("-COMPASS")) write.info(String(sensor.compass()));
    if (command.startsWith("-FIRST COMPASS")) firstCompass();
    if (command.startsWith("-ENABLE CUT")) cut_enabled  = true;
    if (command.startsWith("-DISABLE CUT")) cut_enabled  = false;
    if (command.startsWith("-PANEL AMP")) Serial.println(String(sensor.panelAmp()));
    if (command.startsWith("-PANEL VOLT"))  Serial.println(String(sensor.panelVolts()));
    if (command.startsWith("-ENABLE US")) ultrasonic_enabled = true;
    if (command.startsWith("-DISABLE US")) ultrasonic_enabled = false;
    if (command.startsWith("-DISTANCE 1")) Serial.println(String(sensor.ultrasonic(TRIG_PIN_1, ECHO_PIN_1)));
    if (command.startsWith("-DISTANCE 2")) Serial.println(String(sensor.ultrasonic(TRIG_PIN_2, ECHO_PIN_2)));
    if (command.startsWith("-US SCREENING")){
      while(!write.stop()){
        Serial.print("1: ");
        Serial.println(sensor.ultrasonic(TRIG_PIN_1, ECHO_PIN_1));
        Serial.print("2: ");
        Serial.println(sensor.ultrasonic(TRIG_PIN_2, ECHO_PIN_2));
        delay(200);
      }
    }
  }
}