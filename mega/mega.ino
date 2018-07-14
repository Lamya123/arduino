#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>
#include <LiquidCrystal.h>

SoftwareSerial mySerial(8,9);
LiquidCrystal lcd(7,6,5,4,3,2); // initialize the library with the numbers of the interface pins
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int ledPin = 12;                // choose the pin for the LED
int inputPin = 13;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int pinSpeaker = 11;           //Set up a speaker on a PWM pin (digital 9, 10, or 11)
void setup()
{
    Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");
  // set the data rate for the sensor serial port
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
}
  lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print("Scan your finger");
delay(100);pinMode(ledPin, OUTPUT);      // declare LED as output 
finger.begin(57600);
pinMode(pinSpeaker, OUTPUT);

  pinMode(inputPin, INPUT);     // declare sensor as input
pinMode(10,OUTPUT);
} // set the data rate for the sensor serial port 
  

void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}

uint8_t getFingerprintID( )
{   buzer();
  uint8_t p = finger.getImage();

switch (p){
case FINGERPRINT_OK:
lcd.clear();
lcd.print(" Image taken... ");
delay(1000);
break;
case FINGERPRINT_NOFINGER:
return p;
case FINGERPRINT_PACKETRECIEVEERR:
return p;
case FINGERPRINT_IMAGEFAIL:
return p;
default:
return p; }

// OK success!
p = finger.image2Tz();
switch (p) {
case FINGERPRINT_OK:
break;
case FINGERPRINT_IMAGEMESS:
return p;
case FINGERPRINT_PACKETRECIEVEERR:
return p;
case FINGERPRINT_FEATUREFAIL:
return p;
case FINGERPRINT_INVALIDIMAGE:
return p;
default:
return p; 
}

// OK converted!

p = finger.fingerFastSearch();
if (p == FINGERPRINT_OK )
{    
    delay(300);// sound// turn LED ON


lcd.clear();
lcd.print(" Found match! ");
digitalWrite(10, HIGH);
digitalWrite(ledPin, LOW);
delay(1000);
digitalWrite(10,LOW);
 

   }
else if(p == FINGERPRINT_NOTFOUND )
{   pinMode(pinSpeaker, HIGH);
 delay(300);
lcd.clear();
lcd.setCursor(0,0);
lcd.print(" Did not match! ");
delay(1000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print(" scan finger! ");
return p;
}
else
{ return p; }
// IF FOUND A MATCH............


lcd.clear();
lcd.setCursor(0,0);
lcd.print("Found ID #");
lcd.print(finger.fingerID);
lcd.setCursor(0,1);
lcd.print("confidence ");
lcd.print(finger.confidence);
pinMode(pinSpeaker, LOW);
delay(10000);
 pinMode(pinSpeaker, HIGH);
}

int getFingerprintIDez(){
uint8_t p = finger.getImage();
if (p != FINGERPRINT_OK) return -1;
p = finger.image2Tz();
if (p != FINGERPRINT_OK) return -1;
p = finger.fingerFastSearch();
if (p != FINGERPRINT_OK) return -1;

// found a match!
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Found ID # ");lcd.print(finger.fingerID);
lcd.setCursor(0, 1);
lcd.print("confidence "); lcd.print(finger.confidence);
return finger.fingerID;

}
void buzer(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    playTone(300, 160);
    delay(150);// sound
    digitalWrite(ledPin, LOW);
  }}
  void buzer2(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, LOW);
     playTone(0,0);
    delay(300);// sound// turn LED ON
 pinMode(pinSpeaker, LOW);
  
  }}
void loop() {

getFingerprintID( );


       }
