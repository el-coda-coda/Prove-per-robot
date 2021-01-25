QMC5883LCompass compass;

void compassSET()
{
    String LEVEL = INFO;
    if(LOG_LEVEL == LEVEL)  log(String("compassSET_START"));
    
    unsigned long compassSET = millis();
    
    compass.init();
    delay(100);

    if(LOG_LEVEL == LEVEL)  log(String("FINISHED in ") + String(millis() - compassSET) + String("s"));
}


int compassReadFast()
{
    String LEVEL = VERBOSE;
    compass.read();
    unsigned int Azimuth = compass.getAzimuth();

    if(LOG_LEVEL == LEVEL)  log(String("compassREAD ") + String(Azimuth));
    return Azimuth;
}

int compassReadMedia()
{
    String LEVEL = VERBOSE;
    compass.read();
    int deg_media = 0;
    int i = 0;

    while(i <= 10)
    {
        deg_media += compass.getAzimuth();
        i++;
    }
    deg_media = deg_media/i;

    if(LOG_LEVEL == LEVEL)  log(String("compassREAD ") + String(deg_media));
    return deg_media;
}

int compassDeg (int deg_set, int deg, String direction)
{
    String LEVEL = VERBOSE;
    int deg_final;
    int deg_diff;
  
    if (direction == RIGHT) deg_final = deg_set + deg;
    if (direction == LEFT)   deg_final = deg_set - deg;

    if (deg_final > 360)    deg_final -= 360;
    if (deg_final < 0)  deg_final += 360;

    if (direction == RIGHT)   deg_diff = deg_final - compassReadFast();
    if (direction == LEFT)    deg_diff = compassReadFast() - deg_final;

    delay(10);

    if(LOG_LEVEL == LEVEL)    log(String("DEG_DIFF: ") + String(deg_diff));
    
    return deg_diff;
}

void compassDegDelay(int deg, String direction)
{
    String LEVEL = DEBUG;
    int deg_set = compassReadMedia();
    int deg_cd = deg; //deg_cd = degrees countdown
    deg_threshold = 0 - deg;

    while ((deg_cd > 0) || (deg_cd < deg_threshold)) 
    {
        deg_cd = compassDeg(deg_set, deg, direction);
        if(LOG_LEVEL == LEVEL) log(String("DEG_CD: ") + String(deg_cd));
    }

}