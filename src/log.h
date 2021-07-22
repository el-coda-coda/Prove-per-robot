LiquidCrystal_I2C lcd(0x27,20,4);

bool lcd_initialized = false;
int riga = 0;

void setupLCD() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd_initialized = true;
}


void display_print(int row, String message) {
    if (!lcd_initialized)   setupLCD();
    lcd.setCursor(0,row);
    lcd.print("                    ");
    lcd.setCursor(0, row);
    lcd.print(message);
}

void type(String message) {
    if(LOG_DISPLAY){
        if(riga == 4)  riga = 0;
        display_print(riga, message);
        riga++;
    }
    if(LOG_SERIAL){
        Serial.println(message);
    }
}

class logging{
    public:
    void info(String message);
    void debug(String message);
    void verbose(String message);
    bool stop();
};

void logging::info(String message){
    type(message);
}

void logging::debug(String message){
    if(logLevel < INFO) type(message);
}

void logging::verbose(String message){
    if(logLevel < DEBUG)    type(message);
}

bool logging::stop(){
    if(Serial.available()){
        String command = Serial.readString();
        if (command.startsWith("-STOP")){
            Serial.print(command);
            return true;
        }
        else return false;
    }
}

logging write;