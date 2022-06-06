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
    int ultrasonic(int trig, int echo);
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
    write.info(String("DEG SETUP: " + String(qmc.getAzimuth())));

    //CUTTER AMP
    cutterOffset = 0;
    for(i = 0; i < 50; i++){
        cutterOffset += analogRead(CUTTER_AMP_PIN);
    }
    cutterOffset /= i;
    write.info(String("CUTTER OFFSET: " + String(cutterOffset)));

    //PANEL AMP
    panelOffset = 0;
    for(i = 0; i < 50; i++){
        panelOffset += analogRead(CUTTER_AMP_PIN);
    }
    panelOffset /= i;
    write.info(String("PANEL OFFSET: " + String(panelOffset)));

    //ULTRASONIC
    pinMode(TRIG_PIN_1, OUTPUT);
    pinMode(TRIG_PIN_2, OUTPUT);
    pinMode(ECHO_PIN_1, INPUT);
    pinMode(ECHO_PIN_2, INPUT);

    digitalWrite(TRIG_PIN_1, LOW);
    digitalWrite(TRIG_PIN_2, HIGH);
}

int sensors::battery(){
    digitalWrite(SWITCH_PANEL_PIN, LOW);
    delay(20);
    int bat = (analogRead(BAT_PIN));
    int batPerc = calc.batteryLevel(bat);
    digitalWrite(SWITCH_PANEL_PIN, HIGH);
    return batPerc;
}

bool sensors::setCompass(String slope){
    long compassSET = millis();
    delay(50);
    write.info(String("compassSET in " + String(millis() - compassSET) + " ms" + " " + String(slope)));
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
    write.verbose(String("DG: " + String(deg) + "°"));
    write.verbose(String("COMPASS completed: " + String(millis() - time_set)));
    return deg;
}

float sensors::cutter()  {
    long timeSet = millis();
    float cutterPower = analogRead(CUTTER_AMP_PIN);
    cutterPower = calc.cutterAbsoption(cutterPower);
    write.debug(String("Cutter current absorbed: " + String(cutterPower)));
    write.verbose(String("Cutter power check in: " + String(timeSet - millis()) + " ms"));
    return cutterPower;
}

float sensors::panelVolts() {
    long timeSet = millis();
    int analogPanel = analogRead(READ_PANEL_PIN);
    float voltsPanel = map(analogPanel, 0, 1023, 0, 18000);
    if (voltsPanel < 400) voltsPanel = 0;
    write.debug(String("PANEL: " + String(voltsPanel) + " mV"));
    write.verbose(String("PANELVOLTS completed in: " + String(millis() - timeSet) + " ms"));
    return (voltsPanel/1000);
}

float sensors::panelAmp()   {
    long timeSet = millis();
    float ampPanel = float(analogRead(READ_PANEL_PIN));
    ampPanel = calc.PanelAmp(ampPanel);
    write.debug(String("PANEL: " + String(ampPanel) + " A"));
    write.verbose(String("PANELAMP completed in: " + String(millis() - timeSet) + " ms"));
    return ampPanel;

}

int sensors::ultrasonic(int trig, int echo){
    int distance;
    long timeSet = millis();
    if(ultrasonic_enabled){
        digitalWrite(trig, LOW);
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);

        long duration = pulseIn(echo, HIGH, US_OUTRANGE);
        distance = calc.usDistance(duration);
    }
    else    distance = NO_OBSTACLE;

    write.debug(String("TRIG: " + String(trig) + "; ECHO " + String(echo) + " - DISTANCE " + String(distance)));
    write.verbose(String("US completed in: " + String(millis() - timeSet) + " ms"));
    return distance;
}

sensors sensor;