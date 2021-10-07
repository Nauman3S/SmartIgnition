#include <JC_Button_ESP.h> // https://github.com/maizy/JC_Button

// pin assignments
uint8_t ingitionState = 0;
const byte
    BUTTON_PIN(RELAY_ACTIVATION_BUTTON); // connect a button switch from this pin to ground

Button myBtn(BUTTON_PIN, 100, true); // define the button
const unsigned long LONG_PRESS = 300;

void setupBtn()
{
    myBtn.begin(); // initialize the button object
}

void pollActivationButton()
{

    myBtn.read(); // read the button

    if (myBtn.pressedFor(500))
    {
        if (lastCardAllowed == true)
        {
            Serial.println("Pressed ");
            beepNow(2);
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
