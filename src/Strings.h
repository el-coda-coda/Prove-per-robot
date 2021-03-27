String infoArr[] = {"engineSET", "compassSET"};
String debugArr[] = {"compassCD"};
String verboseArr[] = {"engineON", "engineOFF", "compassREAD", "compassDEG_DIFF", "segmentCURVE"};

//Remeber you have to update the length of the arrays if you want a precise count.


bool StringIdentifier(String message)   {
    for (int i = 0; i < 5; i++) {
        if (message == verboseArr[i]) {
            if (LOG_LEVEL == VERBOSE)   return true;
            else return false;
        }
    }
    for (int i = 0; i < 1; i++) {
        if(message == debugArr[i]) {
            if (LOG_LEVEL == DEBUG)   return true;
            else return false; 
        }
    }
    for (int i = 0; i < 2; i++) {
        if(message == debugArr[i]) {
            if (LOG_LEVEL == INFO)   return true;
            else return false;
        }
    }
    return true;
}