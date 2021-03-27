String infoArr[] = {"engineSET", "compassSET"};
String debugArr[] = {"compassCD"};
String verboseArr[] = {"engineON", "engineOFF", "compassREAD", "compassDEG_DIFF", "segmentCURVE"};

//Remeber you have to update the length of the arrays if you want to add a string in the array
int infoArrLength = 2;
int debugArrLength = 1;
int verboseArrLength = 5;

bool StringIdentifier(String message)   {
    for (int i = 0; i < verboseArrLength; i++) { // if you change the array you have to change the length too
        if (message == verboseArr[i]) {
            if (LOG_LEVEL == VERBOSE)   return true;
            else return false;
        }
    }
    for (int i = 0; i < debugArrLength; i++) { // if you change the array you have to change the length too
        if(message == debugArr[i]) {
            if (LOG_LEVEL == DEBUG)   return true;
            else return false; 
        }
    }
    for (int i = 0; i < infoArrLength; i++) { // if you change the array you have to change the length too
        if(message == debugArr[i]) {
            if (LOG_LEVEL == INFO)   return true;
            else return false;
        }
    }
    return true;
}