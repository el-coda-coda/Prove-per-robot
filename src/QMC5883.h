QMC5883LCompass compass;

void compassSET()
{
    if (LOG_LEVEL == INFO)  log(String("compassSET_START"));
    
    unsigned long compassSET = millis();
    
    compass.init();
    delay(100);

    if (LOG_LEVEL == INFO)  log(String("FINISHED in ") + String(millis() - compassSET) + String("s"));
}


int compassReadFast()
{
    compass.read();
    unsigned int getAzimuth = compass.getAzimuth();

    if (LOG_LEVEL == VERBOSE)  log(String("compassREAD ") + String(getAZimuth));
    return getAzimuth;
}

int compassReadMedia()
{
    compass.read();
    int deg_media = 0;
    int i = 0;

    while(i <= 10)
    {
        deg_media += compass.getAzimuth();
        i++;
    }
    deg_media = deg_media/i;

    if (LOG_LEVEL == VERBOSE)  log(String("compassREAD ") + String(deg_media));
    return deg_media;
}

int compassDeg (int deg_set, int deg, String direction)
{
    int deg_final;
    int deg_diff;
  
    if (direction == RIGHT) deg_final = deg_set + deg;
    if (direction == LEFT)   deg_final = deg_set - deg;

    if (deg_final > 360)    deg_final -= 360;
    if (deg_final < 0)  deg_final += 360;

    if (direction == RIGHT)   deg_diff = deg_final - compassReadFast();
    if (direction == LEFT)    deg_diff = compassReadFast() - deg_final;

    delay(20);

    if(LOG_LEVEL == VERBOSE)    log(String("DEG_DIFF: ") + String(deg_diff));
    
    return deg_diff;
}

void compassDegDelay(int deg, String direction)
{
    int deg_set = compassReadMedia();
    int deg_cd = deg; //deg_cd = degrees countdown
    deg_threshold = 0 - deg;

    while ((deg_cd > 0) || (deg_cd < deg_threshold)) 
    {
        deg_cd = compassDeg(deg_set, deg, direction);
        if(LOG_LEVEL == DEBUG) log(String("DEG_CD: ") + String(deg_cd));
    }

}