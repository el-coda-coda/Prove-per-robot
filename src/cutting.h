Servo esc;
class cut {
    public:
    void off ();
    void on (int speed);
    void setup ();
};

void cut::off() {
    if(CUT_ENABLED) esc.writeMicroseconds(CUT_OFF);
    else write.info(String("Cutting not enabled"));
}

void cut::on (int speed) {
    int cut_speed = map(speed, 0, 100, CUT_OFF, CUT_ON);
    if(CUT_ENABLED) esc.writeMicroseconds(cut_speed);
    else write.info(String("Cutting not enabled"));
}

void cut::setup (){
    if(CUT_ENABLED){
        delay(1000);
        cutter.writeMicroseconds(CUT_OFF);
        delay(3000);
        cutter.writeMicroseconds(CUT_ON);
        delay(3000);
        cutter.writeMicroseconds(CUT_OFF);
    }
}

cut cutter;