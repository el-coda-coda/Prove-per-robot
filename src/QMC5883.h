int compassReadMedia(){
    int deg_media = 0;
    for(int i = 0; i < 15; i++){
        deg_media += sensor.compass();
        delay(1);
    }
    deg_media = deg_media/15;
    write.verbose(String("DG :") + deg_media + String("°"));
    return deg_media;
}
/*
int compassDeg (int deg_set, int deg, String direction) {
    int deg_final;
    int deg_diff;

    if (direction == RIGHT){
        deg_final = deg_set + deg;
        
        if (deg_final > 360){

            deg_final -= 360;
        }
        if (deg_final < 0)  deg_final += 360;


    }

    if (direction == RIGHT)   deg_diff = deg_final - sensor.compass();
    if (direction == LEFT)    deg_diff = sensor.compass() - deg_final;

    delay(10);

    if (direction == LEFT)   deg_final = deg_set - deg;

    write.debug(String("DEG_DIFF: ") + String(deg_diff));
    
    return deg_diff;
}

bool compassDegDelay(int deg, String direction, int deg_set) {
    int deg_cd = deg; //deg_cd = degrees countdown
    deg_threshold = 0 - deg;

    while ((deg_cd > 0) || (deg_cd < deg_threshold)) {
        deg_cd = compassDeg(deg_set, deg, direction);
        deg = sensor.compass();
        write.info(String("DEG_CD: ") + String(deg_cd));
    }
    return true;
}
*/

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