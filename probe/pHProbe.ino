int Vout = 6;  //analogue voltage input
int acidPump = 9;  //digital voltage output to transistor gate for acid
int basePump = 10;  //digital voltage output to transistor gate for base

float pHs = 7.0;  //pH of standard solution
float offset = 0.506;  //offset voltage
float F = 9.6485309e4;  //Faraday's constant
float R = 8.314510;  //universal gas constant
float T = 23.6 + 273.15;  //temperature of solution (K)

void setup() {
  Serial.begin(9600);
//  pinMode(acidPump, OUTPUT);
//  pinMode(basePump, OUTPUT);
}

void loop() {
  float sensorValue = analogRead(Vout);  //sensor value for analogue voltage input
//  ?doesn't work? float VpH = map(sensorValue, 0.0, 1023.0, 0.0, 3.0);
  float Vin = sensorValue*(3.0/1023.0);  //voltage input
  float VpH = Vin - offset;  //voltage produced by probe
  float pHx = pHs + ((VpH*F)/(R*T*log(10)));  //pH of unknown solution

  Serial.println(sensorValue);  //test
  Serial.println(pHx);  //test

//  if(pHx > 5.5) {
//    digitalWrite(acidPump, HIGH);  //supply acid
//    analogWrite(basePump, LOW);  //do not supply base
//  }
//  else if(pHx < 4.5){
//    digitalWrite(basePump, HIGH);  //supply base
//    analogWrite(acidPump, LOW);  //do not supply acid
//  }

  delay(2000);  //test
}
