// Original code by Milan Malesevic and Zoran Stupic
// Thermistor 2 @ Arduino playground

// Code is not yet formated for the Maple
#include <string.h>
#include <wirish/wirish.h>
#include <math.h>

// enumerating the 3 major temperature scales
enum {
    T_KELVIN=0,
    T_CELSIUS,
    T_FAHRENHEIT
};

// Manufacturer data for episco k164 10k thermistor
// simply delete this if you dont need it
// or use this idea to define your own thermistors
#define EPISCO_K164_10k 4300.0f,298.15f,10000.0f // B, T0, R0

// Temperature function outputs float, the actual temperature
// Temperature function inputs
// 1. AnalogInputNumber - analog input to read from
// 2. OutputUnit - output in celsius, kelvin or fahrenheit
// 3. Thermistor B parameter - found in datasheet
// 4. Manufacturer T0 parameter - found in datasheet (kelvin)
// 5. Manufacturer R0 parameter - found in datasheet (ohms)
// 6. Your balance resistor in ohms

float Temperature(int AnalogInputNumber,int OutputUnit,
        float B,float T0,float R0,float R_Balance)
        {
        float R,T;

// R=1024.0f*R_Balance/float(analogRead(AnalogInputNumber))-R_Balance;
R=R_Balance*(1024.0f/float(analogRead(AnalogInputNumber))-1);

T=1.0f/(1.0f/T0+(1.0f/B)*log(R/R0));

switch(OutputUnit){
    case T_CELSIUS:
        T-=273.15f;
        break;
    case T_FAHRENHEIT:
        T=9.0f*(T-273.15f)/5.0f+32.0f;
        break;
    default:
        break;
};

return T;
}
// example of use #1
// reading from analog input 1, using episco l164 definition
// and 10k balance, getting result in celsius

void setup(){
    pinMode(3, INPUT_ANALOG);
}

void loop(){

    SerialUSB.println("*************");
    SerialUSB.println("10k Balance");
    SerialUSB.println(Temperature(3,T_CELSIUS,EPISCO_K164_10k,10000.0f));
    SerialUSB.println("*************");

    delay(500);
}

// Maple setup code

// Force init to be called *first*, i.e. before static object allocation.
// Otherwise, statically allocated objects that need libmaple may fail.

__attribute__((constructor)) void premnain() {
    init();
}

int main(void) {
    setup();

    while (1) {
        loop();
    }
    return 0;
}
