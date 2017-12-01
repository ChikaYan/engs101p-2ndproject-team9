// Program to take input over Serial and then write this as an analogue output for the motor

#define sensorPin P1_5
#define motorPin P2_2

float rpm = 0;
float rpmInput = 0;
int pwmValue = 0;
float rpmMaxPWM = 2000;
volatile int rpmCounter = 0;
unsigned long rpmLastReading = 0;
const unsigned long rpmSampleTime = 3000;

void setup()
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(motorPin, OUTPUT);
  attachInterrupt(sensorPin, rpmInterrupt, FALLING);
}

void loop()
{
  while (Serial.available()) // Grab input from Serial monitor sent by UI program
  {
    Serial.println(millis());
    float input = Serial.parseFloat();
    if (input >= 500 && input <= 1500)
    {
      rpmInput = input;
    }
    pwmValue = getPWMEstimate(rpmInput);
  }

  if (millis() - rpmLastReading >= rpmSampleTime)
  {
    detachInterrupt(sensorPin);    //Disable interrupt when calculating
    rpm = (60000.0 / rpmSampleTime) * (float(rpmCounter) / 2); // 2 interrupts per rotation
    if (rpm < rpmInput)
    {
      pwmValue++;
    }
    if (rpm > rpmInput)
    {
      pwmValue--;
    }

    // output to serial
    Serial.print("RPM =\t");
    Serial.print(rpm);
    Serial.print("\t Hz=\t");
    Serial.print(float(rpmCounter) / 2);
    Serial.print("\t Desired RPM=\t");
    Serial.print(rpmInput);
    Serial.print("\t PWM=\t");
    Serial.println(pwmValue);

    rpmCounter = 0;
    rpmLastReading = millis();
    attachInterrupt(sensorPin, rpmInterrupt, FALLING);
  }

  if (millis() < rpmLastReading) // Handle overflow
  {
    rpmLastReading = 0;
  }

  analogWrite(motorPin, pwmValue); // if using MSP430 to lower voltage, divide this value by 2
  analogWrite(14, pwmValue);
}

int getPWMEstimate(float rpmInput) // Get a rough estimate of the correct PWM value
{
  float m = rpmMaxPWM / 255;
  int pwmEstimate = rpmInput / m;
  return pwmEstimate;
}


void rpmInterrupt()
{
  rpmCounter++;
}
