#include <Servo.h>
#include <dht.h>
#include <SoftwareSerial.h>

#define dht_apin A0

// Initializing Bluetooth, servo, humidity sensor, and LDR pins
SoftwareSerial BTSerial(0, 1);  // RX | TX (Change to pins 2 and 3 for SoftwareSerial)
Servo s1;
dht DHT;

const int ldr_pin = A1;
const int pumpPin = 4;
const int rainPin = 6;

int pumpMode = 0;  // 0 for auto, 1 for manual
int shedMode = 0;

void setup() {
  pinMode(ldr_pin, INPUT);
  pinMode(pumpPin, OUTPUT);
  s1.attach(9);

  Serial.begin(9600);
  BTSerial.begin(9600);  // Adjust the baud rate to match your Bluetooth module
}

void loop() {
  if (BTSerial.available()) {
    char receivedChar = BTSerial.read();

    if (receivedChar == '0') {  // '0' for starting the pump
      pumpMode = 1;
      digitalWrite(pumpPin, HIGH);
    } else if (receivedChar == '1') {  // '1' for stopping the pump
      pumpMode = 1;
      digitalWrite(pumpPin, LOW);
    } else if (receivedChar == '2') {  // '2' for changing pump to auto mode
      pumpMode = 0;
    } else if (receivedChar == '3') {  // '3' for opening the shed
      shedMode = 1;
      s1.write(90);
    } else if (receivedChar == '4') {  // '4' for closing the shed
      shedMode = 1;
      s1.write(0);
    } else if (receivedChar == '5') {  // '5' for changing shed to auto mode
      shedMode = 0;
    }
  }

  DHT.read11(dht_apin);

  // Sending humidity sensor data
  String humidity = String(DHT.humidity);
  Serial.print("H" + humidity + " ");
  Serial.print(DHT.temperature);
  Serial.println(" ");

  // Pump control
  if (pumpMode == 0 && DHT.humidity < 70) {  // Adjust the humidity threshold as needed
    digitalWrite(pumpPin, HIGH);
  } else {
    digitalWrite(pumpPin, LOW);
  }

  // Soil moisture sensor
  int SoilMoistureData = analogRead(A1);
  String StSoilData = String(SoilMoistureData);
  Serial.print("SM" + StSoilData + " ");

  // Rain sensor (assuming it's an LDR)
  int RainData = digitalRead(rainPin);
  Serial.print("R");
  Serial.print(RainData);
  Serial.print(" ");

  // LDR control (for shed)
  if (shedMode == 0) {
    int ldrValue = analogRead(ldr_pin);
    if (ldrValue < 200) {  // Adjust the LDR threshold as needed
      s1.write(0);  // Servo closes
    } else {
      s1.write(90);  // Servo opens
    }
  }
  
  delay(1000);
}


