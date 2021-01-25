int segmentCURVE(int deg, String direction)
{
    String LEVEL = VERBOSE;
    engineON(enginePWR, direction);
    compassDegDelay(deg, direction);
    engineOFF();

    if(LOG_LEVEL == LEVEL)    log(String("SegmentCURVE OFF"));
    return compassReadMedia();
}

bool segmentDegSet()
{
    String LEVEL = INFO;
    unsigned int setDeg = compassReadMedia();
    int setDegRight = segmentCURVE(10, RIGHT);
    bool segmentSituation;

    if ((setDegRight < setDeg) || (setDegRight > (setDeg + 180)))
    {
        if(LOG_LEVEL == LEVEL)  log(String("A DETRA SONO DI MENO"));
        segmentSituation = true;
    }
    else
    {
        if(LOG_LEVEL == LEVEL)  log(String("A SINISTRA SONO DI MENO"));
        segmentSituation = false;
    }
    segmentCURVE(10, LEFT);

    return segmentSituation;
}