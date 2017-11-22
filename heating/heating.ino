#include <math.h>

const int INPIN = 6, OUTPIN = 7;
int expectedT = 30;

void setup()
{
    pinMode(INPIN, INPUT);
    pinMode(OUTPIN, OUTPUT);
}

void loop()
{
    readT();
    adjustHeating(expectedT);
}
