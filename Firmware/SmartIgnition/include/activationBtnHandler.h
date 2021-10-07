#include <JC_Button_ESP.h> // https://github.com/maizy/JC_Button

// pin assignments
uint8_t ingitionState = 0;
const byte
    BUTTON_PIN(RELAY_ACTIVATION_BUTTON); // connect a button switch from this pin to ground

Button myBtn(BUTTON_PIN, 100); // define the button
const unsigned long LONG_PRESS = 200;
unsigned long prevMils = 0;

void setupBtn()
{
    myBtn.begin(); // initialize the button object
}

void pollActivationButton()
{

    myBtn.read(); // read the button
    unsigned long curMils = millis();
    if (myBtn.pressedFor(LONG_PRESS))
    {
        if (curMils - prevMils > 1000)
        {
            prevMils=curMils;

            Serial.println("Pressed ");
            beepNow();
            if (ingitionState == 0)
            {
                digitalWrite(LR_1, HIGH);
                delay(1000);
                digitalWrite(LR_1, LOW);
                ingitionState = 1;
            }
            else if (ingitionState == 1)
            {
                digitalWrite(LR_2, HIGH);
                delay(1000);
                digitalWrite(LR_2, LOW);
                ingitionState = 0;
            }
        }
    }
}
