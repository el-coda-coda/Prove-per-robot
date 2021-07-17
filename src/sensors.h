QMC5883LCompass qmc;

class sensors {
    public:
    void setup();
    int battery();
    bool setCompass(String slope);
    int compass();
    float cutter();
    float panelVolts();
    float panelAmp();
};

void sensors::setup(){
    int i;

    //COMPASS
    qmc.init();
    qmc.setSmoothing(10, true);
    qmc.read();
    for(int i = 0; i < 30; i++){
        qmc.getAzimuth();
        delay(10);
    }
    write.verbose(String("DEG SETUP: ") + String(qmc.getAzimuth()));

    //CUTTER AMP
    cutterOffset = 0;
    for(i = 0; i < 50; i++){
        cutterOffset += analogRead(CUTTER_AMP_PIN);
    }
    cutterOffset /= i;
    write.verbose(String("CUTTER OFFSET: ") + String(cutterOffset));

    //PANEL AMP
    panelOffset = 0;
    for(i = 0; i < 50; i++){
        panelOffset += analogRead(CUTTER_AMP_PIN);
    }
    panelOffset /= i;
    write.info(String("PANEL OFFSET: ") + String(panelOffset));
}

int sensors::battery(){
    digitalWrite(SWITCH_PANEL_PIN, LOW);
    delay(20);
    float bat = BAT_SCALE * float(analogRead(BAT_PIN));
    int bat_100 = 100.0 * (bat - BAT_MIN)/(BAT_MAX - BAT_MIN);
    bat_100 = constrain(bat_100, 0, 100);
    digitalWrite(SWITCH_PANEL_PIN, HIGH);
    return bat_100;
}

bool sensors::setCompass(String slope){
    unsigned long compassSET = millis();
    delay(50);
    write.info(String("compassSET in ") + float (millis() - compassSET)/1000  + String(" s") + String(" ") + slope);
    if(slope == "FLAT") qmc.setCalibration(-600, 900, -600, 1545, -800, 170);
    if(slope == "CUSTOM") return true;
    else{
        write.info(String("PLS insert the slope"));
        return false;
    }
}

int sensors::compass(){
    long time_set = millis();
    qmc.read();
    unsigned int deg = 0;
    for (int i = 0; i < 10; i ++){
        deg += qmc.getAzimuth();
    }
    deg /= 10;
    write.verbose(String("DG: ") + deg + String("°"));
    write.verbose(String("COMPASS COMPLETED IN: ") + String(millis() - time_set));
    return deg;
}

float sensors::cutter()  {
    long timeSet = millis();
    int cutterPower = float(analogRead(CUTTER_AMP_PIN)) - cutterOffset;
    cutterPower = (cutterPower * 5.0/1023.0)/cutterScale;
    cutterPower  = constrain(cutterPower, 0, 5.0);
    write.debug(String("Cutter current absorbed: ") + String(cutterPower));
    write.verbose(String("Cutter power check in: ") + String(timeSet - millis()) + String("s"));
    return cutterPower;
}

float sensors::panelVolts() {
    long timeSet = millis();
    int analogPanel = analogRead(READ_PANEL_PIN);
    float voltsPanel = map(analogPanel, 0, 1023, 0, 18000);
    if (voltsPanel < 400) voltsPanel = 0;
    write.debug(String("PANEL: ") + String(voltsPanel) + String(" mV"));
    write.verbose(String("PANELVOLTS completed in: ") + String(millis() - timeSet) + String(" ms"));
    return (voltsPanel/1000);
}

float sensors::panelAmp()   {
    long timeSet = millis();
    float ampPanel = panelOffset - float(analogRead(READ_PANEL_PIN));
    ampPanel = (ampPanel * 5.0 / 1024.0) / panel_scale;
    ampPanel = constrain(ampPanel, 0, 1.8);
    write.debug(String("PANEL: ") + String(ampPanel) + String(" A"));
    write.verbose(String("PANELAMP completed in: ") + String(millis() - timeSet) + String(" ms"));
    return ampPanel;

}

sensors sensor;