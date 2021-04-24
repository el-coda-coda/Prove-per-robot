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

void segmentStraight(String direction, int distance){ // distance in BOH
    digitalWrite(LED_SETUP, HIGH);
    int set_time = millis();
    int degSet = compassReadMedia();
    delay(50);
    engineON(50, STRAIGHT);
    write.info("STARTED STRAIGHT");
    write.info(String(calc.rotationTime(WHEEL_DIAM, distance, ROTATION_SPEED)) + String(" ms"));
    write.info(String(millis()) + String(" ms"));
    while(millis() - set_time <= calc.rotationTime(WHEEL_DIAM, distance, ROTATION_SPEED)){
        write.info("IN THE WHILE");
        write.info(String("COMPASS: ") + compassStraight(degSet));
        while(compassStraight(degSet).startsWith("RIGHT")){
            int i = 0;
            engineDIR(255, 255 - i);
            delay(50);
            i++; 
        }  
        while(compassStraight(degSet).startsWith("LEFT")){
            int i = 0;
            engineDIR(255 - i, 255);
            delay(50);
            i++;
        }
        engineON(enginePWR, STRAIGHT);
        String command = Serial.readString();
        if (command.startsWith("-STOP")) break;
    }
    write.info("FINISHED WHILE");
    write.info(String("STRAIGHT FINISHED IN ") + String(millis() - set_time) + String(" ms"));
    engineOFF();
    digitalWrite(LED_SETUP, LOW);
}
