class engine {
    public:
    void setup();
    bool on(int power, int direction);
    void off();
};

void engine::setup(){
    pinMode(PWR_A, OUTPUT);
    pinMode(PWR_B, OUTPUT);
    pinMode(DIR_A, OUTPUT);
    pinMode(DIR_B, OUTPUT);
}

bool engine::on(int power, int direction){
    if(drivEngineMessage){
        /*Serial.print("Debug engines ");
        Serial.println(direction);*/
        float realPower = power * 2.55;
        if(direction == back){
            analogWrite(PWR_A, realPower * rightEnginePerc);
            analogWrite(PWR_B, realPower * leftEnginePerc);
            digitalWrite(DIR_A, HIGH);
            digitalWrite(DIR_B, HIGH);
            return true;
        }
        if(direction == forward){
            analogWrite(PWR_A, realPower * rightEnginePerc);
            analogWrite(PWR_B, realPower * leftEnginePerc);
            digitalWrite(DIR_A, LOW);
            digitalWrite(DIR_B, LOW);
            return true;
        }
        if(direction == left){
            analogWrite(PWR_A, realPower * rightEnginePerc);
            analogWrite(PWR_B, realPower * leftEnginePerc * curveSmoothness);
            digitalWrite(DIR_A, HIGH);
            digitalWrite(DIR_B, HIGH);
            return true;
        }
        if(direction == right){
            analogWrite(PWR_A, realPower * rightEnginePerc * curveSmoothness);
            analogWrite(PWR_B, realPower * leftEnginePerc);
            digitalWrite(DIR_A, HIGH);
            digitalWrite(DIR_B, HIGH);
            return true;
        }
        if(direction == OFF){
            analogWrite(PWR_A, 0);
            analogWrite(PWR_B, 0);
            digitalWrite(DIR_A, HIGH);
            digitalWrite(DIR_B, HIGH);
        }
    }
    return false;
}

void engine::off(){
    analogWrite(PWR_A, 0);
    analogWrite(PWR_B, 0);
    digitalWrite(DIR_A, HIGH);
    digitalWrite(DIR_B, HIGH);
}

engine motor;