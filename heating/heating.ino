#include <math.h>

const int INPIN = 6, OUTPIN = 7, OUTPUT_INTERVAL = 100;
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
        expectedT = Serial.parseFloat();
    }
//    if (lastT != expectedT){
//        Serial.println("New temperature is: " + String(expectedT));
//        lastT = expectedT;
//    }
    readT();
    adjustHeating();
}
