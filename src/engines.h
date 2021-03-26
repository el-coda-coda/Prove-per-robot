void engineON(int pwr, String direction)  {
  float pwr_control = pwr * 2.55;

  log(String("engineON_") + String (direction));

  if (direction == STRAIGHT)  {
    analogWrite(PWR_A, pwr_control);
    analogWrite(PWR_B, pwr_control);
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, HIGH);
  }

  if (direction == BACK)  {
    analogWrite(PWR_A, pwr_control);
    analogWrite(PWR_B, pwr_control);
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, LOW);
  }

  if (direction == RIGHT) {
    analogWrite(PWR_A, pwr_control);
    analogWrite(PWR_B, pwr_control);
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, LOW);
  }

  if (direction == LEFT)  {
    analogWrite(PWR_A, pwr_control);
    analogWrite(PWR_B, pwr_control);
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, HIGH);
  }

}

void engineOFF()  {
  log(String("engineOFF"));
  engineON(0, STRAIGHT);
}

void engineSET()  { 
  log(String("engineSET_START"));
  unsigned long engineSETtime = millis();
  pinMode(PWR_A, OUTPUT);
  pinMode(PWR_B, OUTPUT);
  pinMode(DIR_A, OUTPUT);
  pinMode(DIR_B, OUTPUT);
  delay(10);
  log(String("engineSET_COMPLETE"));
}