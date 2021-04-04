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