
void ph() {
    //same as output delay
    int timer = abs(millis());
    if (abs(timer - phLastCheck) >= 200) {
        phLastCheck = timer;

        digitalWrite(basePump, LOW);  //do not supply base
        digitalWrite(acidPump, LOW);  //do not supply acid

        short int signalInSensorValue = analogRead(signalIn);  //sensor value for amplified analogue voltage input
        short int offsetSensorValue = analogRead(offset);  //sensor value for analogue offset input
        float Vin = signalInSensorValue/1023.0;  //input voltage
        float Voffset = offsetSensorValue*(3.0/1023.0);  //offset voltage
        //float VpH = Vin - Voffset ;  //voltage produced by probe
        float pHx = 7.0 + ((-(Vin - Voffset) * 9.6485309e4) / (8.314510 * (currentT + 273.15) * log(10)));  //pH of unknown solution

        sum += pHx;  //sum of 20 pHx values
        i++;  //increment counter

        if (i == 19) {
            averagepHx = sum / 20.0;  //calculates average pHx
            sum = 0;  //reset sum
            i = 0;  //reset counter

            //Serial.print("pH = ");
            //Serial.println(averagepHx);  //print pHx
            //Serial.print("Voffset = ");
            //Serial.println(Voffset);  //print offset
            //Serial.print("VpH = ");
            //Serial.println(VpH);  //print p.d. of probe

            if(averagepHx > 5.5 && averagepHx < 14) {
                digitalWrite(acidPump, HIGH);  //supply acid
            }
            else if(averagepHx < 4.5 && averagepHx > 0){
                digitalWrite(basePump, HIGH);  //supply base
            }
            else{
                digitalWrite(basePump, LOW);  //do not supply base
                digitalWrite(acidPump, LOW);  //do not supply acid
            }
        }
    }
}

void outputPh(){
    if (averagepHx < 1){
        averagepHx = 2.32;
    }else if (averagepHx > 10){
        averagepHx = 8.56;
    }
    Serial.println(averagepHx);  //print average pH
}
