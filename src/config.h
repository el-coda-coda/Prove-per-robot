//driving engines
#define PWR_A   3
#define PWR_B   11
#define DIR_A   4
#define DIR_B   12

int engineThereshold = 100;
int leftEnginePerc = 100/100;
int rightEnginePerc = 100/100;

//cutter engine
#define CUTTER_PIN  8
#define CUTTER_AMP_PIN  1
#define CUT_OFF 1000
#define CUT_ON  2000

bool cutEnabled = false;
float cutterInputScale = 0.88;

//general communications
#define ON  1
#define OFF 0

long back = 1000;
long forward = 2000;
long right = 3000;
long left = 4000;

long output = 0;