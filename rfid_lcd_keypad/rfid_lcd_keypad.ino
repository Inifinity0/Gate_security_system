#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

char keys[ROWS][COLS] = {
  {'#','0','*'},
  {'9','8','7'},
  {'6','5','4'},
  {'3','2','1'}
};

char key_code[3];
char password[3]={'3','2','1'};
int lock =A0;

const int buzzp =  A1;
const int buzzn =  A2;

unsigned int k=0;
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int i=0;
int card1[4]={"13 42 9A CD"};
int card2[4]={"5D 5C 4A 62"};
int card3[4]={87,63,24,178};
int card4[4]={28,45,77,23};

constexpr uint8_t RST_PIN = 9;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 10;     // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 
byte nuidPICC[4];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(lock, OUTPUT);
  pinMode(buzzp, OUTPUT);
  pinMode(buzzn, OUTPUT);
  digitalWrite(lock, HIGH); 
  
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
 
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("  RFID & KEYPAD ");
  lcd.setCursor(0,1);
  lcd.print("  Lock Project  "); 
  lcd.clear();   
  for (byte i = 0; i < 6; i++) {key.keyByte[i] = 0xFF;}
  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));  
  lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
  lcd.setCursor(0, 1);
  lcd.print("Enter the Pass");
}

void loop() {
   
  char key = keypad.getKey();
  
    if(key != NO_KEY){
    //Serial.println(key);
    //Serial.println("pressed:");    
    //Serial.print(i);    
     key_code[i++]=key;
     k=i;
    delay(200);
    digitalWrite(lock, HIGH);
     }
     
 if(k==3){
   //if(key_code[0]=='3'&&key_code[1]=='2'&&key_code[2]=='1'){
   if(!strncmp(password,key_code,3)){
   lcd.clear() ; lcd.setCursor(0, 0);lcd.print("Access Granted");
   digitalWrite(buzzp, HIGH);digitalWrite(buzzn, LOW);delay(100);digitalWrite(buzzp, LOW);digitalWrite(buzzn, LOW);
   digitalWrite(lock, LOW);
   delay(2000);digitalWrite(lock, HIGH); 
   delay(1000);    
    i=k=0;  
  lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
  lcd.setCursor(0, 1);
  lcd.print("Enter the Pass");
   }
 }
  
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

   // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
    Serial.println(nuidPICC[i]);
    }

     if(card1[0] == nuidPICC[0] &&card1[1] == nuidPICC[1] && card1[2] == nuidPICC[2] && card1[3] == nuidPICC[3])
 {
 // digitalWrite(buzzp, HIGH);digitalWrite(buzzn, LOW);delay(100);digitalWrite(buzzp, LOW);digitalWrite(buzzn, LOW);
  lcd.clear() ; lcd.setCursor(0, 0);lcd.print("Access Granted");
  digitalWrite(buzzp, HIGH);digitalWrite(buzzn, LOW);delay(100);digitalWrite(buzzp, LOW);digitalWrite(buzzn, LOW);
  delay(1000);
  digitalWrite(lock, LOW);
  delay(2000);
  digitalWrite(lock, HIGH); 
   lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
  lcd.setCursor(0, 1);
  lcd.print("Enter the Pass");   
 }

 else if(card2[0] == nuidPICC[0] &&card2[1] == nuidPICC[1] && card2[2] == nuidPICC[2] && card2[3] == nuidPICC[3])
 {
  //digitalWrite(buzzp, HIGH);digitalWrite(buzzn, LOW);delay(100);digitalWrite(buzzp, LOW);digitalWrite(buzzn, LOW);
  lcd.clear() ; lcd.setCursor(0, 0);lcd.print("Access Granted");
  digitalWrite(buzzp, HIGH);digitalWrite(buzzn, LOW);delay(100);digitalWrite(buzzp, LOW);digitalWrite(buzzn, LOW);
  delay(1000);
  digitalWrite(lock, LOW);
  delay(2000);
  digitalWrite(lock, HIGH); 
   lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
  lcd.setCursor(0, 1);
  lcd.print("Enter the Pass");   
    
 }
else if(card3[0] == nuidPICC[0] &&card3[1] == nuidPICC[1] && card3[2] == nuidPICC[2] && card3[3] == nuidPICC[3])
 {
  //digitalWrite(buzzp, HIGH);digitalWrite(buzzn, LOW);delay(100);digitalWrite(buzzp, LOW);digitalWrite(buzzn, LOW);
  lcd.clear() ; lcd.setCursor(0, 0);lcd.print("Access Granted");
  digitalWrite(buzzp, HIGH);digitalWrite(buzzn, LOW);delay(100);digitalWrite(buzzp, LOW);digitalWrite(buzzn, LOW);
  delay(1000);
  digitalWrite(lock, LOW);
  delay(2000);
  digitalWrite(lock, HIGH); 
   lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
  lcd.setCursor(0, 1);
  lcd.print("Enter the Pass");   
    
 }
 else if(card4[0] == nuidPICC[0] &&card4[1] == nuidPICC[1] && card4[2] == nuidPICC[2] && card4[3] == nuidPICC[3])
 {
  //digitalWrite(buzzp, HIGH);digitalWrite(buzzn, LOW);delay(100);digitalWrite(buzzp, LOW);digitalWrite(buzzn, LOW);
  lcd.clear() ; lcd.setCursor(0, 0);lcd.print("Access Granted");
  digitalWrite(buzzp, HIGH);digitalWrite(buzzn, LOW);delay(100);digitalWrite(buzzp, LOW);digitalWrite(buzzn, LOW);
  delay(1000);
  digitalWrite(lock, LOW);
  delay(2000);
  digitalWrite(lock, HIGH); 
   lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");
  lcd.setCursor(0, 1);
  lcd.print("Enter the Pass");   
  }
}
  
  
  