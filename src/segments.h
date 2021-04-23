int segmentCURVE(int deg, String direction, int deg_set)
{
    engineON(enginePWR, direction);
    cdDeg(deg_set, direction, deg);
    engineOFF();
    return compassReadMedia();
}

bool segmentDegSet()
{
    String LEVEL = INFO;
    unsigned int setDeg = compassReadMedia();
    int setDegRight = segmentCURVE(10, RIGHT, setDeg);
    bool segmentSituation;

    if ((setDegRight < setDeg) || (setDegRight > (setDeg + 180)))
    {
        //if(LOG_LEVEL == LEVEL)  log(String("A DETRA SONO DI MENO"));
        segmentSituation = true;
    }
    else
    {
        //if(LOG_LEVEL == LEVEL)  log(String("A SINISTRA SONO DI MENO"));
        segmentSituation = false;
    }
    segmentCURVE(10, LEFT, sensor.compass());

    return segmentSituation;
}

void segmentStraight(String direction, int distance){
    int set_time = millis();
    int degSet = compassReadMedia();
    engineON(enginePWR, STRAIGHT);
    while(millis() - set_time <= calc.rotationTime(WHEEL_DIAM, distance, ROTATION_SPEED)){
        while(compassStraight(degSet).startsWith("RIGHT")){
            int i = 0;
            engineDIR(255, 255 - i);
            delay(10);
        }  
        while(compassStraight(degSet).startsWith("LEFT")){
            int i = 0;
            engineDIR(255 - i, 255);
            delay(10);
        }
        engineON(enginePWR, STRAIGHT);
    }

}
