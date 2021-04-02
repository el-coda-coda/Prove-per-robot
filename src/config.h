//In this file we set some general settings

//MOTORS

#define PWR_A   3
#define PWR_B   11

#define DIR_A   4
#define DIR_B   12

unsigned int enginePWR = 0;

//SOLAR PANEL
#define PANEL_PIN   7

//BATTERY
#define BAT_PIN  3
#define BAT_MIN  9.0
#define BAT_MAX 13.8
#define BAT_SCALE   0.054

//QMC5883L
int deg_threshold;

//COMUNICATION

String dir;
String LEFT = "LEFT";
String RIGHT = "RIGHT";
String STRAIGHT = "STRAIGHT";
String BACK = "BACK";
String LOG_LEVEL;
String INFO = "INFO";
String VERBOSE = "VERBOSE";
String DEBUG = "DEBUG";
String FLAT = "FLAT";