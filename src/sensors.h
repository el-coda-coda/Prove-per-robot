class sensors{
   public:
   int batteryLevel(void); 
};

int sensors::batteryLevel(void){
    digitalWrite(SWITCH_PANEL_PIN, LOW);
    delay(20);
    int bat = (analogRead(BAT_PIN));
    int batPerc = 100.0 * ((bat * BAT_SCALE) - BAT_MIN)/(BAT_MAX - BAT_MIN);
    batPerc = constrain(batPerc, 0, 100);
    digitalWrite(SWITCH_PANEL_PIN, HIGH);
    return batPerc;
}

sensors read;