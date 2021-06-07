Servo esc;
class cut {
    public:
    void off ();
    void on (int speed);
    void setup ();
};

void cut::off() { //motor cut stops
    if(CUT_ENABLED) esc.writeMicroseconds(CUT_OFF);
    else write.info(String("Cutting is not enabled"));
}

void cut::on (int speed) { //motor cut rotate from MIN to MAX
    int cut_speed = map((speed * cutterInputScale), 0, 100, CUT_OFF, CUT_ON);
    if(CUT_ENABLED) esc.writeMicroseconds(cut_speed);
    else write.info(String("Cutting is not enabled"));
}

void cut::setup (){ //setup for the esc module
    write.info(String("CUTTER SETUP"));
    esc.writeMicroseconds(CUT_OFF);
    if(CUT_ENABLED){
        delay(1000);
        esc.writeMicroseconds(CUT_OFF);
        delay(3000);
        esc.writeMicroseconds(CUT_ON);
        delay(3000);
        esc.writeMicroseconds(CUT_OFF);
    }
    else write.info(String("Cutting is not enabled"));
}

cut cutter;