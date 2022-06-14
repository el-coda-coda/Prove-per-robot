//driving engines
#define PWR_A   3
#define PWR_B   11
#define DIR_A   4
#define DIR_B   12

int engineThereshold = 100;
float leftEnginePerc = 100/100;
float rightEnginePerc = 100/100;

//cutter engine
#define CUTTER_PIN  8
#define CUTTER_AMP_PIN  1
#define CUT_OFF 1000
#define CUT_ON  2000

bool cutEnabled = false;
float cutterInputScale = 0.88;
float cutterPerc = (50/200 + 0.5); // da 0/200 a 100/200 è il range di potenza

//general communications
#define ON  1
#define OFF 0

long back = 10000;
long forward = 20000;
long right = 30000;
long left = 40000;

long output = 0;