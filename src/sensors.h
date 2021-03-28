class sensors {
    public:
    int battery();
};

int sensors::battery(){
    digitalWrite(PANEL_PIN, LOW);
    delay(20);
    float bat = BAT_SCALE * float(analogRead(BAT_PIN));
    int bat_100 = 100.0 * (bat - BAT_MIN)/(BAT_MAX - BAT_MIN);
    bat_100 = constrain(bat_100, 0, 100);
    digitalWrite(PANEL_PIN, HIGH);
    return bat_100;
}

sensors sensor;