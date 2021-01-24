void engineON(int pwr, String direction)
{

  float pwr_control = pwr * 2.55;

  if (LOG_LEVEL == VERBOSE)  log(String("engineON_") + String (direction));

  if (direction == STRAIGHT)  
  {
    analogWrite(PWR_A, pwr_control);
    analogWrite(PWR_B, pwr_control);
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, HIGH);
    dir = STRAIGHT;
  }

  if (direction == BACK)
  {
    analogWrite(PWR_A, pwr_control);
    analogWrite(PWR_B, pwr_control);
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, LOW);
    dir = BACK;
  }

  if (direction == RIGHT)
  {
    analogWrite(PWR_A, pwr_control);
    analogWrite(PWR_B, pwr_control);
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, LOW);
    dir = RIGHT;
  }

  if (direction == LEFT)
  {
    analogWrite(PWR_A, pwr_control);
    analogWrite(PWR_B, pwr_control);
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, HIGH);
    dir = RIGHT;
  }

}

void engineOFF()
{
  if (LOG_LEVEL == VERBOSE)  log(String("engineOFF"));
  engineON(0, STRAIGHT);
}

void engineSET()
{   
  if (LOG_LEVEL == INFO)  log(String("engineSET_START"));
  unsigned long engineSETtime = millis();
  pinMode(PWR_A, OUTPUT);
  pinMode(PWR_B, OUTPUT);
  pinMode(DIR_A, OUTPUT);
  pinMode(DIR_B, OUTPUT);
  delay(10);

  if (LOG_LEVEL == INFO)  log(String(("FINISHED in  ") + String(millis() - engineSETtime)) + String("s"));
}