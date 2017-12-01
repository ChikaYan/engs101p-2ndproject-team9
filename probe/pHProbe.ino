int signalIn = 6;  //analogue voltage input from probe (pin 6)
int offset = 7;  //offset provided (pin 7)
int acidPump = 9;  //digital voltage output to transistor gate for acid (pin 9)
int basePump = 10;  //digital voltage output to transistor gate for base (pin 10)

float pHs = 7.0;  //pH of standard solution
//float Voffset = 0.506;  //offset voltage
float F = 9.6485309e4;  //Faraday's constant
float R = 8.314510;  //universal gas constant
float T = 23.6 + 273.15;  //temperature of solution (K)

float pHxArray[10];  //array to calculate average pHx
float sum = 0;  //sum of pHxArray
float averagepHx;  //average pHx
int i = 0;  //counter

void setup() {
  Serial.begin(9600);
  pinMode(signalIn, INPUT);  //initialise input
  pinMode(offset, INPUT);  //initialise input
  pinMode(acidPump, OUTPUT);  //initialise output
  pinMode(basePump, OUTPUT);  //initialise output
}

void loop() {
  float signalInSensorValue = analogRead(signalIn);  //sensor value for analogue voltage input
  float offsetSensorValue = analogRead(offset);  //sensor value for analogue offset input
//  ?doesn't work? float VpH = map(sensorValue, 0.0, 1023.0, 0.0, 3.0);
  float Vin = signalInSensorValue*(3.0/1023.0);  //input voltage
  float Voffset = offsetSensorValue*(3.0/1023.0);  //offset voltage
  float VpH = Vin - Voffset;  //voltage produced by probe
  float pHx = pHs + ((-VpH*F)/(R*T*log(10)));  //pH of unknown solution

  if (i < 10) {
      pHxArray[i] = pHx;  //adding pHx value to pHx array
    }
  if (i == 10) {
      i = 0;  //set counter to zero
      sum = 0;  //set sum to zero
    }
  if (i == 9) {
      for (int j = 0; j < 10; j++) {
        sum += pHxArray[j];  //summing all pHx values in pHx array
      }
    averagepHx = sum / 10.0;

    Serial.print('pH = ');
    Serial.println(averagepHx);  //print pHx
    Serial.print('Voffset = ');
    Serial.println(Voffset);  //print offset
    Serial.print('VpH = ');
    Serial.println(VpH);  //print p.d. of probe
    }

  i++;  //counter = counter + 1

  delay(100);  //test

 if(pHx > 5.5) {
   digitalWrite(acidPump, HIGH);  //supply acid
   digitalWrite(basePump, LOW);  //do not supply base
 }
 else if(pHx < 4.5){
   digitalWrite(basePump, HIGH);  //supply base
   digitalWrite(acidPump, LOW);  //do not supply acid
 }
 else {
   digitalWrite(basePump, LOW);  //do not supply base
   digitalWrite(acidPump, LOW);  //do not supply acid
 }
}
