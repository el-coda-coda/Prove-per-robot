class calculate {
    public:
    int rotationTime(int diam, int distance, int rot_speed);
};

int calculate::rotationTime (int diam, int distance, int rot_speed){
    float rot_numb = distance / (diam * 3.14);
    int time = (rot_numb / rot_speed) * 1000;
    return time;
}

calculate calc;