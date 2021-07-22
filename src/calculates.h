class calculate {
    public:
    long rotationTime(int diam, int distance, float rot_speed);
    int batteryLevel(int bat);
    float cutterAbsoption(int cut);
    int usDistance(int duration);
    float PanelAmp(float panel);
    int distaneToDeg(int sideA, int sideB);
};

long calculate::rotationTime (int diam, int distance, float rot_speed){
    float rot_numb = distance / (diam * 3.14);
    long time = (rot_numb / rot_speed) * 1000;
    return time;
}

int calculate::batteryLevel(int bat){
    int bat_100 = 100.0 * ((bat * BAT_SCALE) - BAT_MIN)/(BAT_MAX - BAT_MIN);
    bat_100 = constrain(bat_100, 0, 100);
    return bat_100;
}

float calculate::cutterAbsoption(int cut){
    int cutterAbsorption = cut - cutterOffset;
    cutterAbsorption = (cutterAbsorption * 5.0/1024.0)/cutterScale;
    cutterAbsorption  = constrain(cutterAbsorption, 0, 5.0);
    return cutterAbsorption;
}

int calculate::usDistance(int duration){
    int distance = US_SCALE * (duration/2);
    if(duration > US_OUTRANGE)  distance = NO_OBSTACLE; 
    return distance;
}

float calculate::PanelAmp(float panel){
    panel = ((panelOffset - panel) * 5.0 / 1024.0) / PANEL_SCALE;
    panel = constrain(panel, 0, 1.8);
    return panel;
}

int calculate::distaneToDeg(int sideA, int sideB){ //side A is the "distance" and side b is the width of the robot
    int deg = sideA/(sin(sideB)*DEG_TO_RAD);
    return deg;
}

calculate calc;