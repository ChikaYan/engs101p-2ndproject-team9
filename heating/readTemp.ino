// using thermistor to measure the temperature 
#include <math.h> //for more complex math functions

// set pin numbers to get/send data from/to the components

int tempPin = A0;  //change the number and define please
int ledPin = 13; 

void setup() {
  
  Serial.begin(9600); // 9600 is the baud rate for Serial port
  pinMode(tempPin, INPUT);
  pinMode(ledPin, OUTPUT);  
}

void loop() {
  
 
  
  double currentTemperature;
  int inputTemp; // ADC purposes
  int tempstatus; // for alerting
   inputTemp= analogRead(tempPin); 
  currentTemperature = convertTemperature(inputTemp); // call the function convertTemperature- see below
   
   
  Serial.print(currentTemperature);
 
  delay(500); //change the value to change how often the values should be printed in milliseconds
  tempstatus = temperatureAlert(currentTemperature);
}


// to convert the temperature Steinhart- Hart- Thermistor Equation has been used below
// the equation:  1 / {A + B[ln(R)] + C[ln(R)]^3} where A,B and C are constants
//function to convert the temperature from analog(raw) form to celsius

 double convertTemperature(int rawADC) 
 {

  rawADC -=  200; // Modify the input value to calibrate the temperature
  double Tempo; //temporary variable 
  Tempo = log((10240000/rawADC) - 10000);
    
  //The value constants for the thermistor(4,7k Ohm) and resistor (10k Ohm) being used are:
  // A = 0.001129148, B = 0.000234125 and C = 0.0000000876741
  //the step below gives the temperature in Kelvins;
  
  Tempo = 1 / (0.001129148 + (0.000234125 * Tempo) + (0.0000000876741 * Tempo * Tempo * Tempo)); 
  double tempCel; 
  tempCel = Tempo - 273.15; //subtract 273.15 to get into Celsius
  return tempCel;
 }
 // function to check if the temperature is below certain level and turn on/off the LED(IN OUR CASE WE WILL BE DOING THIS TO THE HEATER)
 int temperatureAlert(int currenttemp)
 {
  if (currenttemp < 8) //change the value as necesaary
  {
    digitalWrite(ledPin, HIGH);
    
  }

  else{
    digitalWrite(ledPin, LOW);
  }
 }
