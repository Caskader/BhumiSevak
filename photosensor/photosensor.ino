#include <Servo.h>
#include "dht.h"

#define dht_apin A0

Servo s1;
dht DHT;

const int ldr_pin = 8;
const int led_pin = 13;

void setup() {
  pinMode(ldr_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  s1.attach(9);

  pinMode(6,INPUT);
  Serial.begin(9600);
}
void loop() {
  DHT.read11(dht_apin);

  Serial.print("Current humidity = ");
  Serial.print(DHT.humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("C  ");

  int SoilMoistureData = analogRead(A1);

  Serial.print("Soil Moisture: ");
  Serial.println(SoilMoistureData);

  int RainData = digitalRead(6);

  Serial.print("Rain data: ");
  Serial.println(RainData);

  int ldrValue = digitalRead(ldr_pin); // Read the LDR pin

  if (ldrValue == HIGH) {
    digitalWrite(led_pin, HIGH); // Turn on the LED when it's dark
    s1.write(0); // Servo closes
  } else {
    digitalWrite(led_pin, LOW); // Turn off the LED when it's light
    s1.write(180); // Servo opens
  }

  Serial.print("LDR value: ");
  Serial.println(ldrValue);

  delay(1000);
}

