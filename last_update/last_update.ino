#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>
#include <LiquidCrystal.h>

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
 
IPAddress ip(192,168,1,10); //IP address for your arduino.

char server[] = "192.168.1.6"; //IP address of your computer.

int interrupt=0; //Variable to control the iterations of void loop().

String rcv=""; //Variable in which the server response is recorded.

EthernetClient client;
SoftwareSerial mySerial(13,12);
LiquidCrystal lcd(8,9,4,5,6,7); // initialize the library with the numbers of the interface pins
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int ledPin = 48;                // choose the pin for the LED
int inputPin = 11;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
int pinSpeaker = 10;           //Set up a speaker on a PWM pin (digital 9, 10, or 11)
void setup()
{ Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit Fingerprint sensor enrollment");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print("Scan your finger");
delay(100);pinMode(ledPin, OUTPUT);      // declare LED as output 
finger.begin(57600);
pinMode(pinSpeaker, OUTPUT);
Ethernet.begin(mac, ip);
  delay(5000);
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
lcd.print("Found ID # ");
lcd.print(finger.fingerID);
lcd.setCursor(0, 1);
lcd.print("confidence ");
lcd.print(finger.confidence);
return finger.fingerID;
 if (client.connect(server, 80)) 
      {
      Serial.println("Connection Established 2");
      client.print("GET /ethernt/data.php?"); //GET request to write data to the database.
      client.print("ID_S=");
      client.print(finger.fingerID);
      client.println(" HTTP/1.1"); 
      client.println("Host: 192.168.1.6"); 
      client.println("Connection: close"); 
      client.println(); 
      client.println(); 
      client.stop();
      }
      else
      {
        Serial.println("Connection failed 2");
      }
 interrupt++; 
 delay(10000); }
 
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
