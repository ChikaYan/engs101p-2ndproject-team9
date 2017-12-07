#include <math.h>

const int OUTPUT_INTERVAL = 5000;

#define signalIn P1_4  //analogue voltage input from probe (pin 6)
#define offset P1_5  //analogue offset input (pin 7)
#define acidPump P2_1  //digital voltage output to transistor gate for acid (pin 9)
#define basePump P2_2  //digital voltage output to transistor gate for base (pin 10)


float sum = 0;  //sum of 20 pHx readings
float averagepHx = 0;  //initialise average pHx
int i = 0;  //counter

//for the stirring motor
#define sensorPin P1_3
#define motorPin P2_0
float rpm = 0;
float rpmInput = 0;
int pwmValue = 0;
volatile int rpmCounter = 0;
unsigned long rpmLastReading = 0;
const unsigned long rpmSampleTime = 5000;

//for the temperature
const int INPIN = 6, OUTPIN = 7;
float expectedT = 30, currentT;
int lastOutput = 0, rawInput;


void setup() {
  Serial.begin(9600);
  //for the pH
  pinMode(signalIn, INPUT);  //initialise input
  pinMode(offset, INPUT);  //initialise input
  pinMode(acidPump, OUTPUT);  //initialise output
  pinMode(basePump, OUTPUT);  //initialise output

  //for temperature
  pinMode(INPIN, INPUT);
  pinMode(OUTPIN, OUTPUT);

  //for the stirring
  pinMode(sensorPin, INPUT);
  pinMode(motorPin, OUTPUT);
  attachInterrupt(sensorPin, rpmInterrupt, FALLING);
}

void loop() {
    takeInputs();
    heating();
    ph();
}

void takeInputs(){
    while (Serial.available()){
        float input = Serial.parseFloat();
        if(input == 0)
        {
          rpmInput = 0;
          pwmValue = 0;
        }
        if (input >= 500 && input <= 1500){
          rpmInput = input;
          pwmValue = getPWMEstimate(rpmInput);
      }else if (input >= 25 && input <= 35){
          expectedT = Serial.parseFloat();
      }
    }
}

void outPutResults(){
    outputT();
    outputRpm();
    outputPh();
}
