bool StringIdentifier(String message)
{
    bool identity = false;

    //VERBOSE - VERBOSE - VERBOSE - VERBOSE
    if (LOG_LEVEL == VERBOSE)
    {
        //engines
        if (message.startsWith("engineON", 0))  identity = true;
        if (message.startsWith("engineOFF", 0)) identity = true;
        //compass
        if (message.startsWith("compassREAD", 0))   identity = true;
        if (message.startsWith("compassDEG_DIFF", 0))   identity = true;
        //segments
        if (message.startsWith("segmentCURVE", 0))   identity = true;

        //DEUG - DEBUG - DEBUG - DEBUG
        if (LOG_LEVEL == DEBUG)
        {
            //engines
            //---------
            //compass
            if (message.startsWith("compassCD", 0))   identity = true;
            //segments

            //INFO - INFO - INFO - INFO
            if (LOG_LEVEL == INFO)
            {
                //engines
                if (message.startsWith("engineSET", 0)) identity = true;
                //compass
                if (message.startsWith("compassSET", 0))    identity = true;
                //segments
            }
        }
    }

    return identity;
}