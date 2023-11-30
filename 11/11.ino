#include <Servo.h>
#include "dht.h"

#define dht_apin A0

Servo s1;
dht DHT;

const int ldr_pin = 8;
const int led_pin = 13;
const int soilMoisture_pin = A1;
const int rainSensor_pin = 6;
const int relay_pin = 7; // Assuming the relay module is connected to digital pin 7

void setup() {
  pinMode(ldr_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  s1.attach(9);

  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, LOW); // Ensure the water pump is initially off

  pinMode(rainSensor_pin, INPUT);
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

  int SoilMoistureData = analogRead(soilMoisture_pin);
  Serial.print("Soil Moisture: ");
  Serial.println(SoilMoistureData);

  int RainData = digitalRead(rainSensor_pin);
  Serial.print("Rain Data: ");
  Serial.println(RainData);

  if (digitalRead(ldr_pin) == HIGH) {
    digitalWrite(led_pin, HIGH);
    s1.write(0); // Servo closes
  } else {
    digitalWrite(led_pin, LOW);
    s1.write(180); // Servo opens
  }

  // Add your conditions for the raindrop sensor and soil moisture sensor here
  if (RainData == HIGH) {
    // It's raining, you can perform an action here (e.g., stop watering)
    digitalWrite(relay_pin, LOW); // Turn off the water pump
  }

  if (SoilMoistureData > 400) {
    // Soil is dry, activate the water pump
    digitalWrite(relay_pin, HIGH); // Turn on the water pump
  } else {
    // Soil has sufficient moisture, turn off the water pump
    digitalWrite(relay_pin, LOW);
  }

  digitalWrite(7,HIGH);

  delay(5000); // Adjust the delay as needed for your monitoring interval
}
