#include <math.h>

const int INPIN = 6, OUTPIN = 7, OUTPUT_INTERVAL = 500;
float expectedT = 30, currentT;
int lastOutput = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(INPIN, INPUT);
    pinMode(OUTPIN, OUTPUT);
}

void loop()
{
    float lastT = expectedT;
    while (Serial.available()){ // read serial input for expected temperature
        if (input >= 25 && input <= 35) {
            expectedT = Serial.parseFloat();
    }
    }
    readT();
    adjustHeating();
}
