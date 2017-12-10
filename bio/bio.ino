#include <math.h>

const int OUTPUT_INTERVAL = 5000;

#define signalIn P1_4  //analogue voltage input from probe (pin 6)
#define offset P1_5  //analogue offset input (pin 7)
#define acidPump P2_1  //digital voltage output to transistor gate for acid (pin 9)
#define basePump P2_2  //digital voltage output to transistor gate for base (pin 10)

float sum = 0;  //sum of 20 pHx readings
float averagepHx = 0;  //initialise average pHx
short int i = 0;  //counter

//for the stirring motor
#define sensorPin P2_5
#define motorPin P2_6
float rpm = 0; // RPM reading from sensor
float rpmInput = 500; // The desired RPM value
short int pwmValue = 130; // This value is written to the MOSFET
volatile short int rpmCounter = 0; // Counts the number of interrupts per time interval


//for the temperature
const short int INPIN = 6, OUTPIN = 7;
float expectedT = 30, currentT = 25;
long lastOutput = 0, mixLastCheck = 0, phLastCheck = 0;


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
  attachInterrupt(sensorPin, rpmInterrupt, FALLING); // Run the function rpmInterrupt everytime the voltage on sensorPin falls. (1->0)
}

void loop() {
  takeInputs();
  heating();
  ph();
  adjustRPM();

  //if the difference between last output time and current time is larger than output interval
  //then output the results and update the last output time
  int timer = abs(millis());
  if (abs(timer - lastOutput) >= OUTPUT_INTERVAL) {
    lastOutput = timer;
    outPutResults();
  }
}

void takeInputs() {
  while (Serial.available()) {
    float input = Serial.parseFloat();
    // distinguish the input by looking at its value
    if (input == 0) { // Quick way to turn off the motor if needed
      rpmInput = 0;
      pwmValue = 0;
    } else if (input >= 500 && input <= 1500) {
      rpmInput = input;
      pwmValue = 130 + ((rpmInput - 500) / (1500 - 500) / (230 - 130)); // Generates an estimate of the PWM value for the desired RPM based off samples taken (assumes linear relationship)
      // at PWM of 130, the RPM was 500
      // at PWM of 230, the RPM was 1500
    } else if (input >= 25 && input <= 35) {
      expectedT = Serial.parseFloat();
    }
  }
}

void outPutResults() {
  outputT();
  outputRpm();
  outputPh();
}
