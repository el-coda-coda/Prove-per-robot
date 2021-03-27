class sensors {
    public:
    int battery();
};

int sensors::battery(){
    digitalWrite(PANEL_PIN, LOW);
    delay(20);
    digitalWrite(PANEL_PIN, HIGH);
}

sensors sensor;


  
  
  
  
  if (type == BATTERY_READ)
  {
    digitalWrite(Panel_PIN, LOW);
    delay(20);
    VBat=VBatScale*float(analogRead(IBAT_PIN));
    VBatPC = 100.0*(VBat-VBat_Level_Min)/(VBat_Level_Max-VBat_Level_Min);
    VBatPC = constrain(VBatPC, 0, 100);
    logInfo(String("Battery charge: ") + String(VBatPC) + String(" %"));
    digitalWrite(Panel_PIN, HIGH);

    long curr_time_end = millis();
    logVerbose(String("Sensor reading duration::BATTERY_READ: ") + String(curr_time_end-curr_time_start));
    return VBatPC;
  }