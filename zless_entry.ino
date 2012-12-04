#include <Keypad.h>
#include <LiquidCrystal.h>

int index = 0;
const int CODESIZE = 4;
char code[CODESIZE+1] = "    ";

const byte PADSIZE = 3;
char keys[PADSIZE][PADSIZE] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
};

byte rowPins[PADSIZE] = { 13, 12, 11 };
byte colPins[PADSIZE] = { 8, 9, 10 };

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, PADSIZE, PADSIZE);

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);  
  lcd.setCursor(0, 0);
  lcd.print("@255.255.255.255");
  lcd.setCursor(0, 1);
  lcd.print("Code? ");
  Serial.begin(9600);
}

void loop() {
  char key = kpd.getKey();
  if (key != NO_KEY) {    
    code[index] = key;
    lcd.setCursor(6+index, 1);
    lcd.print(key);    
    if (++index >= CODESIZE) {
      lcd.setCursor(6, 1);
      if (String(code).equals("1234"))
        lcd.print("Welcome!");
      else
        lcd.print("Try Again!");
      delay(1500);
      lcd.setCursor(6, 1);
      lcd.print("          ");
      index = 0;
    }
      
  }
}
