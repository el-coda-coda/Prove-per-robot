void engineON(int pwr, String direction)
{

  float pwr_control = pwr * 2.55;

  if (direction == STRAIGHT)  
  {
    analogWrite(PWR_A, pwr_control);
    analogWrite(PWR_B, pwr_control);
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, HIGH);
    dir = "STRAIGHT";
  }

  if (direction == BACK)
  {
    analogWrite(PWR_A, pwr_control);
    analogWrite(PWR_B, pwr_control);
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, LOW);
    dir = "BACK";
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
    engineON(0, STRAIGHT);
}

String engineSET()
{   
    log(String("engineSET_START"));
    long engineSETtime = millis();

    pinMode(PWR_A, OUTPUT);
    pinMode(PWR_B, OUTPUT);
    pinMode(DIR_A, OUTPUT);
    pinMode(DIR_B, OUTPUT);
    delay(10);

    return String(("engineSET_FINISHED ") + (millis() - engineSETtime));
}