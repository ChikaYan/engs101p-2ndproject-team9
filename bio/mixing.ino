

void outputRpm(){
    detachInterrupt(sensorPin);    //Disable interrupt when calculating
    rpm = (60000.0 / OUTPUT_INTERVAL) * (float(rpmCounter) / 2); // 2 interrupts per rotation
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

void rpmInterrupt()
{
  rpmCounter++;
}
