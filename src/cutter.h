Servo esc;

class cutter {
    public:
    void setup();
    bool on(int power);
    void off();
};

void cutter::setup(){
    //Serial.println("Debug cutter.setup()");
    Wire.begin();
    pinMode(CUTTER_PIN, OUTPUT);
    digitalWrite(CUTTER_PIN, LOW);
    esc.attach(CUTTER_PIN);
    esc.writeMicroseconds(CUT_OFF);
    if(cutEnabled){
        delay(1000);
        esc.writeMicroseconds(CUT_OFF);
        delay(3000);
        esc.writeMicroseconds(CUT_ON);
        delay(2000);
        esc.writeMicroseconds(CUT_OFF);
    }
    else Serial.println("cutEnabled FALSE");

}

bool cutter::on(int power){
    if(cutEngineMessage){
        int cutSpeed = map((power * cutterInputScale), 0, 100, CUT_OFF, CUT_ON);
        Serial.println(cutSpeed);
        if(cutEnabled)  esc.writeMicroseconds(cutSpeed);
        else    Serial.println("cutEnabled FALSE");
    }
    return cutEnabled;
}

void cutter::off(){
    esc.writeMicroseconds(CUT_OFF);
}

cutter cut;