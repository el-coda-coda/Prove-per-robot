void randomDrive (long distance){
    long timeEffectiveSet = millis(); 
    long timeMovement = calc.rotationTime(WHEEL_DIAM, distance, ROTATION_SPEED);  //time in milliseconds
    unsigned long timeStop = millis() + timeMovement;
    long timePauseSet, timePause;
    while (timeStop < millis()){
        String result = segmentStraight(STRAIGHT, timeStop - millis());
        write.info("RandomDrive return: " + String(result));
        if (result = "CURVE RIGHT"){
            timePauseSet = millis();
            segmentCURVE(90, RIGHT, compassReadMedia());
            timePause = millis() - timePauseSet;
            timeStop += timePause;
        }
        if (result = "CURVE LEFT"){
            timePauseSet = millis();
            segmentCURVE(90, LEFT, compassReadMedia());
            timePause = millis() - timePauseSet;
            timeStop += timePause;
        }
        if (result = "OK") write.info("RandomDrive completed in " + String(millis() - timeEffectiveSet) + "ms");
    }
}