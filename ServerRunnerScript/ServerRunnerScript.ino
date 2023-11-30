#include <Servo.h>
#include "dht.h"
#include <SoftwareSerial.h>
 
#define dht_apin A0
 
 // initialising bluetooth servo and humidity sensor
SoftwareSerial BTSerial(2,3);   // RX | TX
Servo s1;
dht DHT;
 
const int ldr_pin = 8;

int pumpMode = 0; // 0 means auto and 1 means manual mode
int shedMode = 0;
 
void setup() {
  pinMode(ldr_pin, INPUT);// pin for input from the humidity sensor
  pinMode(4,OUTPUT);//pin to control the pump
  s1.attach(9);// attaching a servo at pwm pin 9
  pinMode(6,INPUT);

  Serial.begin(9600);
  BTSerial.begin(9600);
}
 
void loop() {
  // reading input data from the bluetooth module
  if (BTSerial.available()) {
    char receivedChar = BTSerial.read();
    //Serial.println(receivedChar); //uncomment for debug purposes
    if (receivedChar == '0'){// setting command 0 for pump to be started
      pumpMode = 1;
     digitalWrite(4,HIGH);
    }
    if (receivedChar == '1'){// setting command 1 for pump to be stoped
     pumpMode = 1;
      digitalWrite(4,LOW);
   }
    if (receivedChar == 2){//setting command 2 for changing pump to auto mode
      pumpMode = 0; 
    }
    if (receivedChar == '3'){
      shedMode = 1;
      s1.write(90);
    }
    if (receivedChar == '4'){
      shedMode = 1;
      s1.write(0);
    }
    if (receivedChar == '5'){
      shedMode = 0;
    }
  }
  
  // reading humidity sensor data
  DHT.read11(dht_apin);
 
  // sending humidity sensor data
  String humidity = String(DHT.humidity) ;
  Serial.print("H"+humidity+" ");// spaces are for the parser in the client app
  Serial.print(DHT.temperature);
  Serial.println(" C  ");
  
  // controling the pump
  
  if (pumpMode == 0){
    if(DHT.humidity < 700){
      digitalWrite(4,HIGH);
    }else{
      digitalWrite(4,LOW);
    }
  }
  
 
 // reading and sending soil moisture data
  int SoilMoistureData = analogRead(A1);
  String StSoilData = String(SoilMoistureData);
  Serial.print("SM"+StSoilData+" ");
 
 //reading and sending rain data
  int RainData =  digitalRead(6);
  Serial.print("R");
  Serial.print(RainData);
  Serial.print(" ");
 int d= digitalRead(8);
 if( shedMode == 0){
   if (d == HIGH) {
    s1.write(0); // Servo closes
  } else {
    s1.write(90); // Servo opens
  }
 }
  delay(1000);  
}
 
