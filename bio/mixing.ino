

void outputRpm(){
    Serial.print("CRPM"); // Prefix for Python to read
    Serial.println(rpm);
}

void adjustRPM(){
    int timer = abs(millis());
    if (abs(timer - mixLastCheck) >= 1500) {
        mixLastCheck = timer;
        detachInterrupt(sensorPin);    //Disable interrupt when calculating
        rpm = (60000.0 / 1500) * (float(rpmCounter) / 2); // 2 interrupts per rotation
        if (rpm < rpmInput)
        {
          pwmValue += 1;
        }
        if (rpm > rpmInput)
        {
          pwmValue -= 1;
        }
        rpmCounter = 0;
        attachInterrupt(sensorPin, rpmInterrupt, FALLING);
    }
}

void rpmInterrupt()
{
  rpmCounter++;
}
