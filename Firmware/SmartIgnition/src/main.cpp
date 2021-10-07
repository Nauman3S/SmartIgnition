#include <Arduino.h>
#include "statusLED.h"
#include "neoTime.h"
Neotimer StandardTimer(1000);
#define LED 2
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  ledState(ACTIVE_MODE);

}

void loop() {
  // put your main code here, to run repeatedly:
 loopLEDHandler();
 if(StandardTimer.repeat()){
   Serial.println("1 SEC Passed");
 }
}
