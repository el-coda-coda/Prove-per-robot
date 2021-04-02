int compassReadMedia(){
    int deg_media = 0;
    for(int i = 0; i < 10; i++){
        deg_media += sensor.compass();
    }
    deg_media = deg_media/10;
    write.verbose(String("DG :") + deg_media + String("°"));
    return deg_media;
}

int compassDeg (int deg_set, int deg, String direction) {
    int deg_final;
    int deg_diff;

    if (direction == RIGHT) deg_final = deg_set + deg;
    if (direction == LEFT)   deg_final = deg_set - deg;

    if (deg_final > 360)    deg_final -= 360;
    if (deg_final < 0)  deg_final += 360;

    if (direction == RIGHT)   deg_diff = deg_final - sensor.compass();
    if (direction == LEFT)    deg_diff = sensor.compass() - deg_final;

    delay(10);

    write.debug(String("DEG_DIFF: ") + String(deg_diff));
    
    return deg_diff;
}

void compassDegDelay(int deg, String direction) {
    int deg_set = compassReadMedia();
    int deg_cd = deg; //deg_cd = degrees countdown
    deg_threshold = 0 - deg;

    while ((deg_cd > 0) || (deg_cd < deg_threshold)) {
        deg_cd = compassDeg(deg_set, deg, direction);
    }
}