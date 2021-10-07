#include <jled.h>



#define ACTIVE_MODE 0
#define IDLE_MODE 1
#define AP_MODE 2
// blink internal LED every second; 1 second on, 1 second off.
auto led = JLed(LED_BUILTIN).Blink(1000, 1000).Forever();
auto btLed = JLed(BLUETOOTH_CONNECTIVITY).Blink(1000, 1000).Forever();
auto redArmedLed = JLed(LED_R).Blink(1000, 1000).Forever();
auto greenLed = JLed(LED_G).Off().DelayBefore(10);


void ledState(uint8_t v){
    if(v==ACTIVE_MODE){//activve
        led=JLed(LED_BUILTIN).Blink(200, 200).Forever();
    }
    else if(v==IDLE_MODE){//idle
        led=JLed(LED_BUILTIN).Blink(200, 3000).Forever();
    }
    else if(v==AP_MODE){//wifi not connected, ap mode
        led=JLed(LED_BUILTIN).Blink(1000, 1000).Forever();
    }
}

void loopLEDHandler() {
  led.Update();
  btLed.Update();
  redArmedLed.Update();
  greenLed.Update();
}