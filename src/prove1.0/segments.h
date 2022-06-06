int segmentCURVE(int deg, String direction, int deg_set){
    engineOFF();
    for(int i = 0; i < 5; i++){
        write.verbose(String("CURR DEG: " + String(sensor.compass())));
        delay(100);
    }
    firstCompass();
    engineON(enginePWR, direction);
    cdDeg(deg_set, direction, deg);
    engineOFF();
    return compassReadMedia();
}

String segmentStraight (String direction, int distance){
    firstCompass(); //this is for have a "true" degSet
    const int degSet = compassReadMedia();
    long timeSet = millis();
    long timeToArrive = calc.rotationTime(WHEEL_DIAM, distance, ROTATION_SPEED) + timeSet;
    String result = "OK";
    engineON(enginePWR, direction);
    while((!write.stop()) && (result = "OK") && (millis() < timeToArrive)){
        if (!engineON(enginePWR, direction)){
            engineOFF();
            rightEngineDiff = 0;
            leftEngineDiff = 0;
            String curveDirection = angleUS(sensor.ultrasonic(TRIG_PIN_1, ECHO_PIN_1), sensor.ultrasonic(TRIG_PIN_2, ECHO_PIN_2));
            if(curveDirection.startsWith(RIGHT))    curveDirection = RIGHT;
            if(curveDirection.startsWith(LEFT)) curveDirection = LEFT;
            write.info("CURVE " + String(curveDirection));
            result = curveDirection;
        }
        if(compassStraight(degSet) != STRAIGHT){
            if(compassStraight(degSet) == RIGHT)    rightEngineDiff -=2;
            if(compassStraight(degSet) == LEFT)     leftEngineDiff -=2;
        }
        else{
        rightEngineDiff = 0;
        leftEngineDiff = 0;
        }
    }
    engineOFF();
    write.info("segmentSTRAIGHT completed in: " + String(millis() - timeSet) + " ms; TimeToArrive: " + String(millis() - timeToArrive));
    rightEngineDiff = 0;
    leftEngineDiff = 0;
    return result;
}