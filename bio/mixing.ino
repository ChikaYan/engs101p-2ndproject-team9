

void outputRpm() {
  Serial.println(rpm);
}

void adjustRPM() {
  //same as output delays
  int timer = abs(millis());
  if (abs(timer - mixLastCheck) >= 1500) { // If 1500ms has passed
    detachInterrupt(sensorPin); // Disable interrupt when calculating
    rpm = (60000.0 / 1500) * (float(rpmCounter) / 2); // 2 interrupts per rotation so divide by 2, multiply by how many time intervals in 1 minute
    if (rpm < rpmInput) // If the current RPM reading is too low, increase the PWM value
    {
      pwmValue += 1;
    }
    if (rpm > rpmInput) // If the current RPM reading is too high, decrease the PWM value
    {
      pwmValue -= 1;
    }
    rpmCounter = 0;
    mixLastCheck = timer;
    attachInterrupt(sensorPin, rpmInterrupt, FALLING); // Enable the interrupt again
  }
  analogWrite(motorPin, pwmValue);
}

void rpmInterrupt() // This function is run everytime an interrupt occurs
{
  rpmCounter++;
}
