void engineON(int pwr, String direction)
{

  pwr_control = pwr * 2.55;

  if (direction == String("STRAIGHT"))  
  {
    analogWrite(PW_A, pwr_control);
    analogWrite(PW_B, pwr_control);
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, HIGH);
    dir = "STRAIGHT";
  }

  if (direction == String("BACK"))
  {
    analogWrite(PW_A, pwr_control);
    analogWrite(PW_B, pwr_control);
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, LOW);
    dir = "BACK";
  }

  if (direction == RIGHT)
  {
    analogWrite(PW_A, pwr_control);
    analogWrite(PW_B, pwr_control);
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, LOW);
    dir = RIGHT;
  }

  if (direction == LEFT)
  {
    analogWrite(PW_A, pwr_control);
    analogWrite(PW_B, pwr_control);
    digitalWrite(DIR_A, LOW);
    digitalWrite(DIR_B, HIGH);
    dir = RIGHT;
  }

}

void engineOFF()
{
    engineON(0, STRAIGHT);
}