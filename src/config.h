//In this file we set some general settings

//ENGINES

#define PWR_A   3
#define PWR_B   11

#define DIR_A   4
#define DIR_B   12

#define WHEEL_DIAM  12 //in centimeters
#define ROTATION_SPEED  0.33 // 20 RPM, 0.33333 rotations for second

unsigned int enginePWR = 100;
int leftEngineDiff = 0;
int rightEngineDiff = 0;

//CUTTER
#define CUTTER_PIN  8
#define CUTTER_AMP_PIN  1 //the analog pin where read the consumption of the motor for cutting
#define CUT_OFF 1000
#define CUT_ON_MAX  2000

int cutterOffset = 0;
float cutterScale = 0.185;  //motor cut current scale V/A
float cutterInputScale = 0.88;
bool cut_enabled  = false;

//SOLAR PANEL
#define SWITCH_PANEL_PIN   7
#define READ_PANEL_PIN  2
#define PANEL_SCALE 0.185

float panelOffset = 0;

//BATTERY
#define BAT_PIN  3
#define BAT_MIN  9.0
#define BAT_MAX 13.8
#define BAT_SCALE   0.054

//ULTRASONIC SENSORS
#define TRIG_PIN_1  5
#define TRIG_PIN_2  6
#define ECHO_PIN_1  2
#define ECHO_PIN_2  13

#define US_OUTRANGE 38000
#define US_SCALE    0.034
#define NO_OBSTACLE 1000

bool ultrasonic_enabled = true;
int stop_distance = 70;

//QMC5883L
int deg_threshold;

//COMUNICATION
#define INFO    3
#define DEBUG   2
#define VERBOSE 1
String dir;
String LEFT = "LEFT";
String RIGHT = "RIGHT";
String STRAIGHT = "STRAIGHT";
String BACK = "BACK";
int logLevel;
String FLAT = "FLAT";
String CUSTOM = "CUSTOM";
bool LOG_SERIAL = true; // or OFF for don't log on the serial
bool LOG_DISPLAY = true; // or OFF for don't log on the display

//MATHS
#define RADIANTS_TO_DEG 57.30     // 1 deg = 0.0174533 radians

//DIMENSIONS OF THE ROBOT
#define WIDTH   40