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


void log(String message) 
{
    if(riga == 4)  riga = 0;
    display_print(riga, message);
    riga++;
}