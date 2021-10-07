
auto beepPiezo = JLed(PEIZO).Blink(250, 250).Repeat(3);

void setupBeeper()
{
    pinMode(PEIZO, OUTPUT);
}
void beepNow(int times)
{
    beepPiezo = JLed(PEIZO).Blink(250, 250).Repeat(times);
}
void loopBeepHandler()
{
    beepPiezo.Update();
}