#include <math.h>

#define INPIN 6
#define OUTPIN 7

void setup()
{
    pinMode(inpin, INPUT);
    pinMode(outpin, OUTPUT);
}

void loop()
{
    measureTemp()
    adjustHeating()
}
