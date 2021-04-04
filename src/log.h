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
};

void logging::info(String message){
    if(LOG_LEVEL == INFO || LOG_LEVEL == DEBUG || LOG_LEVEL == VERBOSE)   type(message);
}

void logging::debug(String message){
    if(LOG_LEVEL == DEBUG || LOG_LEVEL == VERBOSE)  type(message);
}

void logging::verbose(String message){
    if(LOG_LEVEL == VERBOSE)    type(message);
}

logging write;