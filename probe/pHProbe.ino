int signalIn = 6;  //analogue voltage input from probe (pin 6)

int offset = 7;  //offset provided (pin 7)

int acidPump = 9;  //digital voltage output to transistor gate for acid (pin 9)

int basePump = 10;  //digital voltage output to transistor gate for base (pin 10)

float sum = 0;

float pHs = 7.0;  //pH of standard solution

//float Voffset = 0.506;  //offset voltage

float F = 9.6485309e4;  //Faraday's constant

float R = 8.314510;  //universal gas constant

float T = 24.1 + 273.15;  //temperature of solution (K)

int i = 0;
float average;

void setup() {

  Serial.begin(9600);

  pinMode(signalIn, INPUT);

  pinMode(offset, INPUT);

  pinMode(acidPump, OUTPUT);
  pinMode(basePump, OUTPUT);

}



void loop() {
  
  float signalInSensorValue = analogRead(signalIn);  //sensor value for analogue voltage input

  float offsetSensorValue = analogRead(offset);  //sensor value for analogue offset input

//  ?doesn't work? float VpH = map(sensorValue, 0.0, 1023.0, 0.0, 3.0);

  float Vin = signalInSensorValue*(3.0/1023.0);  //input voltage

  float Voffset = offsetSensorValue*(3.0/1023.0);  //offset voltage

  float VpH = Vin - Voffset;  //voltage produced by probe

  float pHx = pHs + ((-VpH*F)/(R*T*log(10)));  //pH of unknown solution



  //test






  float pHxArray[10];
    
  if (i < 10)
    {
      pHxArray[i] = pHx;
    }
    
  if (i == 10)
    {
      i = 0;
      sum = 0;
    }    
    
  if (i == 9)
    {
      for (int j = 0; j < 10; j++)
      {
        sum = sum + pHxArray[j];
      }
      average = sum / 10;
      Serial.println(average);
    }
    
   
   
   
    i++;
    
      if( average > 5.5) {

    digitalWrite(acidPump, HIGH);  //supply acid

    digitalWrite(basePump, LOW);  //do not supply base

  }

  else if(average < 4.5){

    digitalWrite(basePump, HIGH);  //supply base

    digitalWrite(acidPump, LOW);  //do not supply acid
  }

  else {

    digitalWrite(basePump, LOW);

  digitalWrite(acidPump, LOW);
  }
    
    delay(100);
    
    
    
    
//      Serial.println(signalInSensorValue);
//  Serial.println(offsetSensorValue);  //test
//
//  Serial.println(pHx);
  


}
