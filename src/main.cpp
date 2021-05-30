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

void setup() {
  pinMode(LED_SETUP, OUTPUT);
  pinMode(PANEL_PIN, OUTPUT);
  digitalWrite(LED_SETUP, HIGH);
  LOG_LEVEL = INFO;
  Wire.begin();
  Serial.begin(115200); 
  engineSET();
  sensor.setCompass(CUSTOM);
  write.info(String("BAT: ") + String(sensor.battery()) + String(" %"));

  delay(2000);
  write.verbose(String("First compass: ") + compassReadMedia());
  digitalWrite(LED_SETUP, LOW);
}

String qmcCalibration() {
  int calibrationData[3][2];
  bool changed = false;
  bool done = false;
  int t = 0;
  int c = 0;

  while (true){
    int x, y, z;
  
  // Read compass values
  qmc.read();

  // Return XYZ readings
  x = qmc.getX();
  y = qmc.getY();
  z = qmc.getZ();

  changed = false;

  if(x < calibrationData[0][0]) {
    calibrationData[0][0] = x;
    changed = true;
  }
  if(x > calibrationData[0][1]) {
    calibrationData[0][1] = x;
    changed = true;
  }

  if(y < calibrationData[1][0]) {
    calibrationData[1][0] = y;
    changed = true;
  }
  if(y > calibrationData[1][1]) {
    calibrationData[1][1] = y;
    changed = true;
  }

  if(z < calibrationData[2][0]) {
    calibrationData[2][0] = z;
    changed = true;
  }
  if(z > calibrationData[2][1]) {
    calibrationData[2][1] = z;
    changed = true;
  }

  if (changed && !done) {
    Serial.println("CALIBRATING... Keep moving your sensor around.");
    c = millis();
  }
    t = millis();
  
  
  if ( (t - c > 5000) && !done) {
    done = true;
    Serial.println("DONE. Copy the line below and paste it into your projects sketch.);");
    Serial.println();
      
    Serial.print("compass.setCalibration(");
    Serial.print(calibrationData[0][0]);
    Serial.print(", ");
    Serial.print(calibrationData[0][1]);
    Serial.print(", ");
    Serial.print(calibrationData[1][0]);
    Serial.print(", ");
    Serial.print(calibrationData[1][1]);
    Serial.print(", ");
    Serial.print(calibrationData[2][0]);
    Serial.print(", ");
    Serial.print(calibrationData[2][1]);
    Serial.println(");");
    qmc.setCalibration(calibrationData[0][0], calibrationData[0][1], calibrationData[1][0], calibrationData[1][1], calibrationData[2][0], calibrationData[2][1]);
    return String(calibrationData[0][0] + String(" ") + calibrationData[0][1] + String(" ") + calibrationData[1][0] + String(" ") + calibrationData[1][1] + String(" ") + calibrationData[2][0] + String(" ") + calibrationData[2][1]);
    }
  }
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
  }
}