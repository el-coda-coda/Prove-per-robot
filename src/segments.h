string segmentCURVE(int deg, String direction)
{
    engineON(enginePWR, direction);
    compassDegDelay(deg, direction);
    engineOFF()

    if(LOG_LEVEL == VERBOSE)    log(String("SegmentCURVE OFF"));
    return String("SegmentCURVE FINISHED");
}

