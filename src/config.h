//In this file we set some general settings

//MOTORS

#define PWR_A   3
#define PWR_B   11

#define DIR_A   4
#define DIR_B   12

#define WHEEL_DIAM  12 //in centimeters
#define ROTATION_SPEED  0.42 // 25 RPM, 0.4167 rotztion for second

unsigned int enginePWR = 75;

#define CUTTER_PIN  8
#define CUTTER_AMP_PIN  1 //the analog pin where read the consumption of the motor for cutting
#define CUT_ENABLED  true
#define CUT_OFF 1000
#define CUT_ON  2000

int cutterOffset = 0;
float cutterScale = 0.185;  //motor cut current scale V/A
float cutterInputScale = 0.88;

//SOLAR PANEL
#define PANEL_PIN   7

//BATTERY
#define BAT_PIN  3
#define BAT_MIN  9.0
#define BAT_MAX 13.8
#define BAT_SCALE   0.054

//SETUP LED PIN
#define LED_SETUP   13

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
String CUSTOM = "CUSTOM";
bool LOG_SERIAL = true; // or OFF for don't log on the serial
bool LOG_DISPLAY = true; // or OFF for don't log on the display