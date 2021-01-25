int segmentCURVE(int deg, String direction)
{
    engineON(enginePWR, direction);
    compassDegDelay(deg, direction);
    engineOFF();

    if(LOG_LEVEL == VERBOSE)    log(String("SegmentCURVE OFF"));
    return compassReadMedia();
}

bool segmentDegSet()
{
    unsigned int setDeg = compassReadMedia();
    int setDegRight = engineCURVE(10, RIGHT);
    bool segmentSituation;

    if ((setDegRight < setDeg) || (setDegRight > (setDeg + 180))
    {
        if (LOG_LEVEL == INFO)  log(String("A DETRA SONO DI MENO"));
        segmentSituation = true;
    }
    else
    {
        if (LOG_LEVEL == INFO)  log(String("A SINISTRA SONO DI MENO"));
        segmentSituation = false;
    }
    engineCURVE(10, LEFT);

    return segmentSituation;
}