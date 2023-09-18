#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include<Servo.h>
#include <Keypad.h>
Servo myservo;
int pos =0;


#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
String UID ="13 42 9A CD";
byte lock = 0;

LiquidCrystal_I2C lcd(0x27, 20, 4);
MFRC522 rfid(SS_PIN, RST_PIN);


// Define keypad layout
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 2, 1, 0}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char correctCode[] = "1234"; // Change this to your desired code
char enteredCode[5]; // Buffer to store entered code
int codeIndex = 0;

void setup() {
  lcd.clear();
  lcd.init();
  lcd.backlight();
  lcd.print("Enter code:");
  myservo.attach(3);


Serial.begin(9600);
SPI.begin();
rfid.PCD_Init();
pinMode(7,OUTPUT);

}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      if (strcmp(enteredCode, correctCode) == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Correct Code");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter code:");
        resetCode();
        for(pos=90;pos>=0;pos-=1)
        {myservo.write(pos);
        delay(15);
       // break;
        //myservo.write(0);
        }
        delay(3000);
        for(pos=0;pos<=90;pos+=1)
        {myservo.write(pos);
        delay(15);
        }
        
      
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Incorrect Code");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter code:");
        resetCode();
      }
    } else {
      enteredCode[codeIndex++] = key;
      lcd.setCursor(codeIndex - 1, 1);
      lcd.print('*');
      if (codeIndex == 5) {
        codeIndex = 0;
      }
    }
  }



lcd.setCursor(0, 2);
lcd.print("Tap Your Card");

if ( ! rfid.PICC_IsNewCardPresent())
return;
if ( ! rfid.PICC_ReadCardSerial())
return;

lcd.clear();
lcd.setCursor(0, 2);
lcd.print("Scanning");
Serial.print("NUID tag is :");
String ID = "";
for (byte i = 0; i < rfid.uid.size; i++) {
lcd.print(".");
ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
ID.concat(String(rfid.uid.uidByte[i],HEX));
delay(300);
}
ID.toUpperCase();

if (ID.substring(1) == UID && lock == 0 ) {
for(pos=0; pos<=150; pos+=1){
    myservo.write(pos);
    delay(15);
  }
lcd.clear();
lcd.setCursor(0, 2);
lcd.print("Door is locked");
delay(1500);
lcd.clear();
lock = 1;
} else if (ID.substring(1) == UID && lock == 1 ) {
 for(pos=150; pos>=0; pos-=1){
    myservo.write(pos);
    delay(15);
  }
lcd.clear();
lcd.setCursor(0, 2);
lcd.print("Door is open");
delay(1500);
lcd.clear();
lock = 0;
} else {
lcd.clear();
lcd.setCursor(0, 2);
lcd.print("Wrong card!");
delay(1500);
lcd.clear();
}




}

void resetCode() {
  memset(enteredCode, 0, sizeof(enteredCode));
  codeIndex = 0;
  lcd.setCursor(0, 1);
  lcd.print("                "); // Clear the code display
}
