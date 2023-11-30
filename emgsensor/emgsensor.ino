//EMG sensor robotic hand controller 
//This code is for controlling a robotic hand with
//an EMG sensor. 
//
//© Au Robots 8.4.2017


//Necessary for controlling the ser
///// This is the reference value and it
//will depend on your setup. You have to find it out 
//yourself by looking at the serial monitor and finding
//a value between the maximum and minimum value.

//Naming the servos


void setup() 
{ 
//Starting the serial monitor
Serial.begin(9600); 

} 

void loop() 
{ 
//Printing the EMG data
Serial.println(analogRead(5)); 

//If the EMG data is greater than x the hand clo

//If the EMG data is lower than x the hand op

//A delay to slow down the process
  delay(100);
} 
