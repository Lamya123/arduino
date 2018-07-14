boolean x;
void setup(){
  pinMode(13,INPUT);
  pinMode(5,OUTPUT);
  Serial.begin (9600);
  
}
void loop (){
  x=digitalRead(13);
  if (x==1){
    digitalWrite(5,HIGH);
    delay(5);
      Serial.println("There is motion");
  }
  if (x==0){
    digitalWrite(5,LOW);
    delay(5);
      Serial.println("no motion");
    
  }
}

