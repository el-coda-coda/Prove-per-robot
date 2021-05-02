int deg_media = 0;
int i = 0;

int compassReadMedia(){
    for(i = 0; i < 50; i++){
        deg_media += sensor.compass();
        delay(2);
    }
    deg_media = deg_media/50;
    write.verbose(String("DEG :") + deg_media + String("°"));
    return deg_media;
}

bool cdDeg (int deg_set, String direction, int deg){
    if (direction == LEFT){
        int deg_in = deg_set;
        int deg_final = deg_set - deg;
        int deg_diff_part = 0; // = deg_final - 360; // con questo prendo quanto sotto zero va la deg diff
        if(deg_final < 0)    deg_final += 360;
        if(deg_in < deg_final){
            deg_diff_part = deg - deg_set;
            deg_final = 0;
            deg_in += deg_diff_part;
        }

        write.debug(String("---COMPASS---"));
        write.debug(String("SET: ") + String(deg_set));
        write.debug(String("DIR: " + direction));
        write.debug(String("DEG: ") + String(deg));
        write.debug(String("DEG_IN: ") + String(deg_in));
        write.debug(String("DEG_FIN: ") + String(deg_final));
        write.verbose(String("DEG_PART: ") + String(deg_diff_part));
        write.verbose(String("DEG_DIFF: ") + String(deg_final-deg_in));

        while((deg_in > deg_final) && ((deg_final-deg_in) > - 300)){
            deg_in = compassReadMedia() + deg_diff_part;
            if(deg_in > 360) deg_in -= 360;
            write.verbose(String("DEG_IN: ") + String(deg_in));
            write.verbose(String("DEG_FIN: ") + String(deg_final));
            delay(5);
        }
        write.debug(String("-------------"));
        return  true;
    }

    if (direction == RIGHT){
        int deg_in = deg_set;
        int deg_final = deg_set + deg;
        int deg_diff_part = 0; // = deg_final - 360; // con questo prendo quanto sotto zero va la deg diff
        if(deg_final >= 360)    deg_final -= 360;
        if(deg_in > deg_final){
            deg_diff_part = 360 - deg_set;
            deg_final = deg;
            deg_in += deg_diff_part;
        }
        if(deg_in >= 360) deg_in -= 360;

        write.debug(String("---COMPASS---"));
        write.debug(String("SET: ") + String(deg_set));
        write.debug(String("DIR: " + direction));
        write.debug(String("DEG: ") + String(deg));
        write.debug(String("DEG_IN: ") + String(deg_in));
        write.debug(String("DEG_FIN: ") + String(deg_final));
        write.verbose(String("DEG_PART: ") + String(deg_diff_part));
        write.verbose(String("DEG_DIFF: ") + String(deg_final-deg_in));

        while((deg_in < deg_final)){
            deg_in = compassReadMedia() + deg_diff_part;
            if(deg_in >= 360) deg_in -= 360;
            write.verbose(String("DEG_PART: ") + String(deg_diff_part));
            write.verbose(String("DEG_DIFF: ") + String(deg_final-deg_in));
            delay(5);
        }
        write.debug(String("-------------"));
        return  true;
    }

    write.info("INVALID DIRECTION: " + String(direction));
    return false;
}

String compassStraight (int deg_set){
    String result = "OK";
    int deg = compassReadMedia(); //deg is the live deg from the compass
    long timeSet = millis();
    write.info(String("DEG: ") + String(deg));
    write.info(String("DEG SET: ") + String(deg_set));
    int deg_diff = 0;
    if (deg_set > deg){
        result = "RIGHT";
        deg_diff = deg_set - deg;
    }
    
    if(deg_set < deg - 300){
        result = "RIGHT";
        deg_diff = 360 - deg_set + deg;
    }

    if (deg_set < deg ){
        result = "LEFT";
        deg_diff = deg - deg_set;
    }

    if (deg_set > deg + 300){
        result = "LEFT";
        deg_diff = 360 - deg + deg_set;
    }
    write.info(String("C_STRAIGHT FINISHED IN ") + String(millis() - timeSet) + String(" ms"));
    return String(result + " " + String(deg_diff));
}

int compassCalibration(){

    int calibrationData[3][2];
    bool changed = false;
    bool done = false;
    int t = 0;
    int c = 0;
    int x, y, z;
  
    // Read compass values
    qmc.read();

    // Return XYZ readings
    x = qmc.getX();
    y = qmc.getY();
    z = qmc.getZ();

    changed = false;

    if(x < calibrationData[0][0]) {
        calibrationData[0][0] = x;
        changed = true;
    }
    if(x > calibrationData[0][1]) {
        calibrationData[0][1] = x;
        changed = true;
    }

    if(y < calibrationData[1][0]) {
        calibrationData[1][0] = y;
        changed = true;
    }
    if(y > calibrationData[1][1]) {
        calibrationData[1][1] = y;
        changed = true;
    }

    if(z < calibrationData[2][0]) {
        calibrationData[2][0] = z;
        changed = true;
    }
    if(z > calibrationData[2][1]) {
        calibrationData[2][1] = z;
        changed = true;
    }

    if (changed && !done) {
        engineON(100, RIGHT);
        c = millis();
    }
        t = millis();
    
    
    if ( (t - c > 5000) && !done) {
        done = true;
        write.info("DONE");
        write.info(String(calibrationData[0][0] + calibrationData[0][1] +calibrationData[1][0] + calibrationData[1][1] + calibrationData[2][0] + calibrationData[2][1]));
        }
    engineOFF();
    int calibrationArray[6] {calibrationData[0][0], calibrationData[0][1], calibrationData[1][0], calibrationData[1][1], calibrationData[2][0], calibrationData[2][1]};
    return calibrationArray[6];
}