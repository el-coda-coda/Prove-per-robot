QMC5883LCompass qmc;

class sensors {
    public:
    void setup();
    int battery();
    bool setCompass(String slope);
    int compass();
    float cutter();
};

void sensors::setup(){
    //COMPASS
    qmc.init();
    qmc.setSmoothing(10, true);
    //CUTTER AMP
    cutterOffset = 0;
    int i;
    for(i = 0; i < 50; i++){
        cutterOffset += analogRead(CUTTER_AMP_PIN);
    }
    cutterOffset /= i;
}

int sensors::battery(){
    digitalWrite(PANEL_PIN, LOW);
    delay(20);
    float bat = BAT_SCALE * float(analogRead(BAT_PIN));
    int bat_100 = 100.0 * (bat - BAT_MIN)/(BAT_MAX - BAT_MIN);
    bat_100 = constrain(bat_100, 0, 100);
    digitalWrite(PANEL_PIN, HIGH);
    return bat_100;
}

bool sensors::setCompass(String slope){
    unsigned long compassSET = millis();
    delay(50);
    write.info(String("compassSET in ") + float (millis() - compassSET)/1000  + String(" s") + String(" ") + slope);
    if(slope == "FLAT") qmc.setCalibration(-468, 877, 0, 1523, -787, 0);
    if(slope == "CUSTOM") return true;
    else{
        write.info(String("PLS insert the slope"));
        return false;
    }
}

int sensors::compass(){
    qmc.read();
    unsigned int deg = 0;
    for (int i = 0; i < 5; i ++){
        deg += qmc.getAzimuth();
        delay(3);
    }
    deg /= 5;
    write.verbose(String("DG: ") + deg + String("°"));
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

sensors sensor;