#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Sim800l.h>
#include <SoftwareSerial.h> 

LiquidCrystal_I2C lcd(16, 2);
Sim800l Sim800l;  //to declare the library
const byte relay = A0;

char* number ="082165062273";
bool error; //to catch the response of sendSms
String sms;     // to storage the text of the sms
byte index = 1;   // to indicate the message to read.
String line1;
void setup() {
  // put your setup code here, to run once:
  lcd.autoAddress();
  lcd.begin();
  pinMode(relay, OUTPUT);
    lcd.setCursor(0,0);
  lcd.print("Init SIM800");
  delay(1000);
  Sim800l.begin(); // initializate the library. 
  error=Sim800l.delAllSms(); //clean memory of sms;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Init SMS Sukses");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ready...");
}

void loop() {
  // put your main code here, to run repeatedly:
  sms=Sim800l.readSms(index);// untuk membaca sms dengan no 1, sms pertama.... 
   if (sms.length() > 7)  // optional you can avoid SMS empty
   {
    Serial.println(sms); 
    sms.toUpperCase(); // menjadi kan isi sms boleh huruf besar maupun huruf kecil
      if (sms.indexOf("ON")!=-1){
         digitalWrite(relay, HIGH);
         line1 = "relay hidup";
      }
      else if (sms.indexOf("OFF")!=-1){
         digitalWrite(relay, LOW);
         line1 = "relay mati.";
      }
      else{
       Serial.println("SMS tidak valid...");
      }
       lcd.setCursor(0,1);
       lcd.print(line1);
       Serial.println("Delet sms.....");
       Sim800l.delAllSms(); 
       
   }
}
