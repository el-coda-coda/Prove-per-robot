QMC5883LCompass qmc;

class sensors {
    public:
    int battery();
    bool setCompass(String slope);
    int compass();
};

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
    qmc.init();
    qmc.setSmoothing(10, true);
    delay(50);
    if(slope == "FLAT") qmc.setCalibration(-468, 877, 0, 1523, -787, 0);
    else{
        write.info(String("PLS say the slope"));
        return false;
    }
    write.info(String("compassSET in ") + float (millis() - compassSET)/1000  + String(" s"));
    return true;
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

sensors sensor;