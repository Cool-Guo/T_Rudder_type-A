//------------------------------------------------------------
// T-Rudder
// MCU: Arduino Pro Micro
// ADC: ADS1115
// Sersor: A1324LUA-T
// bin.guo@siid.ac.cn
// 2019-02-21 - V1
//------------------------------------------------------------

#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include "Joystick.h"

#define DELAY_TIME 10

// Rudder Setting
int16_t centerValue = 11000;  // Input param
int16_t maxValue = 21400; // Input param
int16_t minValue = 1640;  // Input param
int16_t deadZone = 50;  // Input param
int16_t rudderOut;
int16_t outMin = -32768;  // rudder output  minvalue
int16_t outMax = 32767; // rudder output maxvalue

// ADS1115 Setting
Adafruit_ADS1115 ads;  
int16_t adc0; // Input from rudder
float multiplier = 0.1875F; // ADS1115  @ +/- 6.144V gain (16-bit results) 

// USB Joystick library Setting. Only using rudder axis
Joystick_ Joystick(0x12, 
  JOYSTICK_TYPE_JOYSTICK, 0, 0,
  false, false, false, false, false, false,
  true, false, false, false, false);

// Mapping Value
void convertRudder(int16_t value)
{
  if (((value-centerValue)>0 && (value-centerValue)<deadZone) || ((value-centerValue)<0 && (value-centerValue)>-deadZone)){
    Joystick.setRudder(0);
  }else if (value<minValue){
    Joystick.setRudder(outMin);
  }else if (value>maxValue){
    Joystick.setRudder(outMax);
  }else{
    if (value>=(centerValue+deadZone)){
      rudderOut = (value-centerValue-deadZone)*outMax/(maxValue-centerValue-deadZone);
    }else if (value<=(centerValue-deadZone)){
      rudderOut = (centerValue-value-deadZone)*outMin/(centerValue-minValue-deadZone);
    }
    Joystick.setRudder(rudderOut);
  }
}  

void originalOut(int16_t value)
{
  //centerValue = (minValue+maxValue)/2;
  if (value<minValue){
    Joystick.setRudder(minValue);
  }else if (value>maxValue){
    Joystick.setRudder(maxValue);
  }else{
    Joystick.setRudder(value);
  }
}  

void setup() {
  //Serial.begin(9600);
  
  //Joystick.setRudderRange(outMin, outMax);
  Joystick.setRudderRange(minValue, maxValue);
  Joystick.begin();
  ads.begin();
}

void loop() {
  adc0 = ads.readADC_SingleEnded(0);
  //Serial.print("AIN0: "); Serial.println(adc0); //For reading Input param
  //Serial.print("("); Serial.print(adc0 * multiplier); Serial.println("mV)");  ////For reading Input param
  //Serial.println(" ");
  //convertRudder(adc0);
  originalOut(adc0);
  //Joystick.sendState();
  delay(DELAY_TIME);
  
}
