#include <math.h>

const int INPIN = 6, OUTPIN = 7;
int expectedT = 30;

void setup()
{
    Serial.begin(9600);
    pinMode(INPIN, INPUT);
    pinMode(OUTPIN, OUTPUT);
}

void loop()
{
    readT();
    delay(1000);
    //adjustHeating(expectedT);
}
