#include <math.h>

const int INPIN = 6, OUTPIN = 7, OUTPUT_INTERVAL = 500;
float expectedT = 30;

void setup()
{
    Serial.begin(9600);
    pinMode(INPIN, INPUT);
    pinMode(OUTPIN, OUTPUT);
}

void loop()
{
    while (Serial.available()){ // read serial input for expected temperature
        expectedT = Serial.parseFloat();
    }
    //readT();
    //adjustHeating(expectedT);
}
