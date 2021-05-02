class calculate {
    public:
    long rotationTime(int diam, int distance, float rot_speed);
};

long calculate::rotationTime (int diam, int distance, float rot_speed){
    float rot_numb = distance / (diam * 3.14);
    long time = (rot_numb / rot_speed) * 1000;
    return time;
}

calculate calc;