// using thermistor to measure the temperature

#include <math.h>

void readT(){
    float currentT;
    int rawInput;
    rawInput = analogRead(INPIN);
    currentT = convertTemperature(rawInput);
}

// to convert the temperature Steinhart- Hart- Thermistor Equation has been used below
// the equation:  1 / {A + B[ln(R)] + C[ln(R)]^3} where A,B and C are constants
// function to convert the temperature from analog(raw) form to celsius
double convertTemperature(int rawADC){
    rawADC -=  200; // Modify the input value to calibrate the temperature
    double Tempo; // temporary variable
    Tempo = logf((10240000/rawADC) - 10000);
    //The value constants for the thermistor(4,7k Ohm) and resistor (10k Ohm) being used are:
    // A = 0.001129148, B = 0.000234125 and C = 0.0000000876741
    //the step below gives the temperature in Kelvins;
    Tempo = 1 / (0.001129148 + (0.000234125 * Tempo) + (0.0000000876741 * Tempo * Tempo * Tempo));
    double tempCel;
    tempCel = Tempo - 273.15; //subtract 273.15 to get into Celsius
    return tempCel;
}
