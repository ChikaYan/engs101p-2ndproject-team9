// Program to take input over Serial and then write this as an analogue output for the motor

#define sensorPin P1_5
#define motorPin P2_2

float rpm = 0;
float rpmInput = 0;
int pwmValue = 0;
volatile int rpmCounter = 0;
unsigned long rpmLastReading = 0;
const unsigned long rpmSampleTime = 1500;

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
    float input = Serial.parseFloat(); // TODO: Might need to check for prefix here.
    if(input == 0)
    {
      rpmInput = 0;
      pwmValue = 0;
    }
    if (input >= 500 && input <= 1500)
    {
      rpmInput = input;
    }
    pwmValue = getPWMEstimate(rpmInput);
  }

  if (millis() - rpmLastReading >= rpmSampleTime) // Enough time has passed to sample RPM
  {
    detachInterrupt(sensorPin);    //Disable interrupt when calculating
    rpm = (60000.0 / rpmSampleTime) * (float(rpmCounter) / 2); // 2 interrupts per rotation
    if (rpm < rpmInput)
    {
      pwmValue += 1;
    }
    if (rpm > rpmInput)
    {
      pwmValue -= 1;
    }
    Serial.print("CRPM"); // Prefix for Python to read
    Serial.println(rpm);

    rpmCounter = 0;
    rpmLastReading = millis();
    attachInterrupt(sensorPin, rpmInterrupt, FALLING);
  }

  if (millis() < rpmLastReading) // Handle overflow
  {
    rpmLastReading = 0;
  }

  analogWrite(motorPin, pwmValue);
}

int getPWMEstimate(float rpmInput) // Get a rough estimate of the correct PWM value
{
  float m = (1500 - 500) / (230 - 130);
  int pwmEstimate = 130 + ((rpmInput-500) / m);
  return pwmEstimate;
}

void rpmInterrupt()
{
  rpmCounter++;
}
