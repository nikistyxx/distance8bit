/*
Adafruit Arduino - Lesson 9. Light sensing
*/
#define VCNL4000_ADDRESS 0x13
#include <DistanceGP2Y0A21YK.h>
DistanceGP2Y0A21YK Dist;
int distance;
int lightPin = 0;
int latchPin = 5;
int clockPin = 6;
int dataPin = 4;
 
int leds = 0;
 
void setup() 
{
    Serial.begin(9600);
  Dist.begin(A0);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}
 
void loop() 
{
  int reading  = analogRead(lightPin);
  
  // Linearize Sharp GP2Y0A02YK
  distance = Dist.getDistanceCentimeter();
float distance = 21208 * pow(reading, -1.251);  // inches

 
  int numLEDSLit = distance / 9;  //1023 / 9 / 2
  if (numLEDSLit > 8) numLEDSLit = 8;
  leds = 0;
  for (int i = 0; i < numLEDSLit; i++)
  {
    bitSet(leds, i); 
  }
  updateShiftRegister();
  
 
  Serial.print("\nDistance in centimers: ");
  Serial.print(distance);  
  delay(500); //make it readable
}
 
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
