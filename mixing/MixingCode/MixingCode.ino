// Program to take input over Serial and then write this as an analogue output for the 'motor'

#define sensorPin PUSH2 // Replace these with correct pin numbers
#define motorPin P2_0

float rpm = 0;
float rpmInput = 0;
int pwmValue = 0;

volatile int rpmCounter = 0;
unsigned long rpmLastReading = 0;
const unsigned long rpmSampleRate = 20;

void setup()
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT_PULLUP); // Remove _PULLUP for real thing
  attachInterrupt(sensorPin, rpmInterrupt, FALLING);
}

void loop()
{
  while (Serial.available()) // Grab input from Serial monitor
  {
    Serial.println("READING");
    Serial.println(millis());
    float input = Serial.parseFloat();
    if (input >= 500 && input <= 1500)
    {
      rpmInput = input;
    }
  }

  if (rpmCounter > rpmSampleRate) // More precise way to measure RPM
  {
    detachInterrupt(sensorPin);    //Disable interrupt when calculating
    rpm = (60000.0 / (millis() - rpmLastReading)) * (float(rpmCounter) / 2); // 2 interrupts per rotation

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

  if(millis() < rpmLastReading) // Handle overflow
  {
    rpmLastReading = 0;
  }

  // if current rpm < wanted rpm,
  // increase the pwm by 1 each second, but getting a measurement every few seconds?
  analogWrite(motorPin, pwmValue);
}


void rpmInterrupt()
{
  rpmCounter++;
}
