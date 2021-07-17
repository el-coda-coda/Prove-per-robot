int segmentCURVE(int deg, String direction, int deg_set){
    engineOFF();
    for(int i = 0; i < 5; i++){
        write.verbose(String("CURR DEG: ") + String(sensor.compass()));
        delay(100);
    }
    firstCompass();
    engineON(enginePWR, direction);
    cdDeg(deg_set, direction, deg);
    engineOFF();
    return compassReadMedia();
}

void segmentStraight(String direction, int distance){ // distance in BOH
    const int degSet = compassReadMedia();
    int standardVel = enginePWR;
    delay(50);
    write.info(String("STARTED STRAIGHT"));
    write.info(String(calc.rotationTime(WHEEL_DIAM, distance, ROTATION_SPEED)) + String(" ms"));
    write.info(String(millis()) + String(" ms"));
    long set_time = millis();
    while((millis() - set_time) <= calc.rotationTime(WHEEL_DIAM, distance, ROTATION_SPEED)){
        digitalWrite(LED_SETUP, HIGH);
        write.info("IN THE WHILE");
        write.info(String("COMPASS: ") + compassStraight(degSet));
        int i = 0;
        engineON(enginePWR, STRAIGHT);
        while(compassStraight(degSet).startsWith("RIGHT")){
            engineDIR(standardVel, standardVel - i);
            i++; 
            write.info("GOING LEFT");
        }  
        engineON(50, STRAIGHT);
        while(compassStraight(degSet).startsWith("LEFT")){
            engineDIR(standardVel - i, standardVel);
            i++;
            write.info("GOING RIGHT");
        }
        String command = Serial.readString();
        if (command.startsWith("-STOP")) break;
    }
    write.info("FINISHED WHILE");
    write.info(String("STRAIGHT FINISHED IN ") + String(millis() - set_time) + String(" ms"));
    engineOFF();
    digitalWrite(LED_SETUP, LOW);
}
