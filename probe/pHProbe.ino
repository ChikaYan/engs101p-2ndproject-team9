#define signalIn P1_4  //analogue voltage input from probe (pin 6)
#define offset P1_5  //analogue offset input (pin 7)
#define acidPump P2_1  //digital voltage output to transistor gate for acid (pin 9)
#define basePump P2_2  //digital voltage output to transistor gate for base (pin 10)

float pHs = 7.0;  //pH of standard solution
float F = 9.6485309e4;  //Faraday's constant
float R = 8.314510;  //universal gas constant
float T = 24.2 + 273.15;  //temperature of solution (K)

float sum = 0;  //sum of 20 pHx readings
float averagepHx = 0;  //initialise average pHx
int i = 0;  //counter

void setup() {
  Serial.begin(9600);
  pinMode(signalIn, INPUT);  //initialise input
  pinMode(offset, INPUT);  //initialise input
  pinMode(acidPump, OUTPUT);  //initialise output
  pinMode(basePump, OUTPUT);  //initialise output
}

void loop() {
  if(millis() % 200 == 0) { //checks pHx every 2 seconds, adds acid/base for 2/10 second
    digitalWrite(basePump, LOW);  //do not supply base
    digitalWrite(acidPump, LOW);  //do not supply acid
  
    float signalInSensorValue = analogRead(signalIn);  //sensor value for amplified analogue voltage input
    float offsetSensorValue = analogRead(offset);  //sensor value for analogue offset input
    float Vin = signalInSensorValue/1023.0;  //input voltage
    float Voffset = offsetSensorValue*(3.0/1023.0);  //offset voltage
    float VpH = Vin - Voffset;  //voltage produced by probe
    float pHx = pHs + ((-VpH*F)/(R*T*log(10)));  //pH of unknown solution
    
    sum += pHx; //sum of 10 pHx values
    i++;  //increment counter
  
    if (i == 19) {
      averagepHx = sum / 20.0; //calculates average pHx
      sum = 0;  //reset sum
      i = 0;  //reset counter
  
      Serial.print("pH = ");
      Serial.println(averagepHx);  //print pHx
      // Serial.print("Voffset = ");
      // Serial.println(Voffset);  //print offset
      // Serial.print("VpH = ");
      // Serial.println(VpH);  //print p.d. of probe
  
      if(averagepHx > 5.5 && averagepHx < 14) {
       digitalWrite(acidPump, HIGH); //supply acid
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
