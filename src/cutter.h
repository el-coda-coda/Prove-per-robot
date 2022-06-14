Servo esc;

class cutter {
    public:
    void setup();
    bool on(int power);
    void off();
};

void cutter::setup(){
    esc.writeMicroseconds(CUT_OFF);
    if(cutEnabled){
        delay(1000);
        esc.writeMicroseconds(CUT_OFF);
        delay(3000);
        esc.writeMicroseconds(CUT_ON);
        delay(3000);
        esc.writeMicroseconds(CUT_OFF);
    }
    else Serial.println("cutEnabled FALSE");
}

bool cutter::on(int power){
    int cutSpeed = map((power * cutterInputScale), 0, 100, CUT_OFF, CUT_ON);
    if(cutEnabled)  esc.writeMicroseconds(cutSpeed);
    else{
        Serial.println("cutEnabled FALSE");
        return false;
    }
    return true;
}

void cutter::off(){
    esc.writeMicroseconds(CUT_OFF);
}