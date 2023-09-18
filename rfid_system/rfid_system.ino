
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#include<Servo.h>
Servo myservo;
int pos=0;




#define SS_PIN 10
#define RST_PIN 9
String UID ="13 42 9A CD";
byte lock = 0;

LiquidCrystal_I2C lcd(0x27, 20, 4);
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
myservo.attach(3);

Serial.begin(9600);
lcd.init();
lcd.backlight();
SPI.begin();
rfid.PCD_Init();
pinMode(7,OUTPUT);
}

void loop() {
lcd.setCursor(0, 0);
lcd.print("Tap Your Card");

if ( ! rfid.PICC_IsNewCardPresent())
return;
if ( ! rfid.PICC_ReadCardSerial())
return;

lcd.clear();
lcd.setCursor(0, 0);
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
lcd.setCursor(0, 0);
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
lcd.setCursor(0, 0);
lcd.print("Door is open");
delay(1500);
lcd.clear();
lock = 0;
} else {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Wrong card!");
delay(1500);
lcd.clear();
}
}