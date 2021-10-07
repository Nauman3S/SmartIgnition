
auto beepPiezo = JLed(PEIZO).Blink(250, 250).Repeat(3);

void setupBeeper()
{
    pinMode(PEIZO, OUTPUT);
}
void beepNow()
{
    beepPiezo = JLed(PEIZO).Blink(250, 250).Repeat(3);
}
void loopBeepHandler()
{
    beepPiezo.Update();
}