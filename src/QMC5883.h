QMC5883LCompass compass;

void compassSET()
{
    log(String("compassSET_START"));
    
    unsigned long compassSET = millis();
    
    compass.init();
    delay(100);

    log(String("FINISHED in ") + String(millis() - compassSET) + String("s"));
}


int compassReadFast()
{
    compass.read();
    unsigned int getAzimuth = compass.getAzimuth();

    log(String("compassREAD ") + String(getAZimuth));
    return getAzimuth;
}

int compassReadMedia()
{
    compass.read();
    int def_media = 0;
    int i = 0;

    while(i <= 10)
    {
        def_media += compass.getAzimuth();
        i++;
    }
    def_media = def_media/i;
    return def_media;
}

int compassDeg (int deg_set, int deg, String direction)
{
    int deg_final;
    int deg_diff;
  
    if (direction == String("RIGHT")) deg_final = deg_set + deg;
    if (direction == String("LEFT"))   deg_final = deg_set - deg;

    if (deg_final > 360)    deg_final -= 360;
    if (deg_final < 0)  deg_final += 360;

    if (direction == String("RIGHT"))   deg_diff = deg_final - compassReadFast();
    if (direction == String("LEFT"))    deg_diff = compassReadFast() - deg_final;

    delay(20);
    
    return deg_diff;
}

void compassDegDelay(int deg, String direction)
{
    int deg_set = compassReadMedia();
    int deg_cd = deg;
    deg_threshold = 0 - deg;

    while ((deg_cd > 0) || (deg_cd < deg_threshold)) 
    {
        deg_cd = compassDeg(deg_set, deg, direction);
        log(String("DEG_CD: ") + String(deg_cd));
    }

}