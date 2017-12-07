

void outputRpm(){
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
    attachInterrupt(sensorPin, rpmInterrupt, FALLING);
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
