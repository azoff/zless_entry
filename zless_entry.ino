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
  lcd.print("@127.0.0.1");
  lcd.setCursor(0, 1);
  lcd.print("Code? ");
  Serial.begin(9600);
}

void print(char *message) {
  lcd.setCursor(6, 1);
  lcd.print(message);
}

void loop() {
  char key = kpd.getKey();
  if (key != NO_KEY) {    
    code[index] = key;
    print(code);
    if (++index >= CODESIZE) {
      print("Sending");
      Serial.println(code);
      Serial.flush();
      print("Waiting");
      while (Serial.available() <= 0);
      char response = (char) Serial.read();
      print("Checking");
      if (response == '1') print("Welcome!  ");
      else                 print("Try Again!");
      delay(2500);
      print("          ");
      code[0] = code[1] = code[2] = code[3] = ' ';
      index   = 0;
    }
      
  }
}
