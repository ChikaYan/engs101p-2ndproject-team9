int signalIn = 6;  //analogue voltage input from probe (pin 6)
int offset = 7;  //offset provided (pin 7)
int acidPump = 9;  //digital voltage output to transistor gate for acid (pin 9)
int basePump = 10;  //digital voltage output to transistor gate for base (pin 10)

float pHs = 7.0;  //pH of standard solution
//float Voffset = 0.506;  //offset voltage
float F = 9.6485309e4;  //Faraday's constant
float R = 8.314510;  //universal gas constant
float T = 23.6 + 273.15;  //temperature of solution (K)

void setup() {
  Serial.begin(9600);
  pinMode(signalIn, INPUT);
  pinMode(offset, INPUT);
//  pinMode(acidPump, OUTPUT);
//  pinMode(basePump, OUTPUT);
}

void loop() {
  float signalInSensorValue = analogRead(signalIn);  //sensor value for analogue voltage input
  float offsetSensorValue = analogRead(offset);  //sensor value for analogue offset input
//  ?doesn't work? float VpH = map(sensorValue, 0.0, 1023.0, 0.0, 3.0);
  float Vin = signalInSensorValue*(3.0/1023.0);  //input voltage
  float Voffset = offsetSensorValue*(3.0/1023.0);  //offset voltage
  float VpH = Vin - Voffset;  //voltage produced by probe
  float pHx = pHs + ((VpH*F)/(R*T*log(10)));  //pH of unknown solution

  Serial.println(signalInSensorValue - offsetSensorValue);  //test
  Serial.println(pHx);  //test

//  if(pHx > 5.5) {
//    digitalWrite(acidPump, HIGH);  //supply acid
//    digitalWrite(basePump, LOW);  //do not supply base
//  }
//  else if(pHx < 4.5){
//    digitalWrite(basePump, HIGH);  //supply base
//    digitalWrite(acidPump, LOW);  //do not supply acid
//  }
//  else {
//    digitalWrite(basePump, LOW);
//    digitalWrite(acidPump, LOW);
//  }

  delay(2000);  //test
}
