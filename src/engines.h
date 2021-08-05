bool engineON(int pwr, String direction)  {
  float pwr_control = pwr * 2.55;
  if(angleUS(sensor.ultrasonic(TRIG_PIN_1, ECHO_PIN_1), sensor.ultrasonic(TRIG_PIN_2, ECHO_PIN_2)) == STRAIGHT){
    if (direction == BACK)  {
      analogWrite(PWR_A, pwr_control + rightEngineDiff);
      analogWrite(PWR_B, pwr_control + leftEngineDiff);
      digitalWrite(DIR_A, HIGH);
      digitalWrite(DIR_B, HIGH);
    }

    if (direction == STRAIGHT)  {
      analogWrite(PWR_A, pwr_control + rightEngineDiff);
      analogWrite(PWR_B, pwr_control + leftEngineDiff);
      digitalWrite(DIR_A, LOW);
      digitalWrite(DIR_B, LOW);
    }

    if (direction == LEFT) {
      analogWrite(PWR_A, pwr_control + rightEngineDiff);
      analogWrite(PWR_B, pwr_control + leftEngineDiff);
      digitalWrite(DIR_A, HIGH);
      digitalWrite(DIR_B, LOW);
    }

    if (direction == RIGHT)  {
      analogWrite(PWR_A, pwr_control + rightEngineDiff);
      analogWrite(PWR_B, pwr_control + leftEngineDiff);
      digitalWrite(DIR_A, LOW);
      digitalWrite(DIR_B, HIGH);
    }
    write.verbose(String("engine_ON " + String(direction)));
    return true;
  }
  else return false;
}

void engineOFF()  {
  write.verbose(String("engine_OFF "));
  engineON(0, STRAIGHT);
}

void engineSET()  { 
  long timeSet = millis();
  pinMode(PWR_A, OUTPUT);
  pinMode(PWR_B, OUTPUT);
  pinMode(DIR_A, OUTPUT);
  pinMode(DIR_B, OUTPUT);
  delay(100);
  write.info(String("engineSET in " + String(millis() - timeSet) + " ms"));
}