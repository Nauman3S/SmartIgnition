#include <Arduino.h>
#include "pinsDef.h"
#include "statusLED.h"
#include "neoTime.h"
#include "beepHandler.h"
#include "mfrcHandler.h"
#include "activationBtnHandler.h"
#include "accessControlList.h"

Neotimer StandardTimer(1000);
#define LED 2
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  ledState(ACTIVE_MODE);
  setupRFID();
  setupAccessControlList();
  addAllowedNUID("3219320124");
  setupBtn();
  setupBeeper();

  
  pinMode(LED_B, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_Y, OUTPUT);

  pinMode(LR_OFF,OUTPUT);
  pinMode(LR_1,OUTPUT);
  pinMode(LR_2,OUTPUT);
  digitalWrite(LR_OFF,HIGH);//turn off all relays
  delay(1000);
  digitalWrite(LR_OFF,LOW);
  
  for (int i = 0; i < 2; i++)
  {
    digitalWrite(PEIZO, LOW);
    delay(250);
    digitalWrite(PEIZO, HIGH);
    delay(250);
  }

  for (int i = 0; i < 4; i++)
  {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_Y, HIGH);
    delay(500);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_Y, LOW);
    delay(500);
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  loopLEDHandler();
  if (StandardTimer.repeat())
  {
    Serial.println("1 SEC Passed");
  }

  loopRFID();
  pollActivationButton();
  loopBeepHandler();
}
